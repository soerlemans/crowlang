// STL Includes:
#include <fstream>

// Includes:
#include "ast/node/fdecl.hpp"
#include "ast/node/include.hpp"
#include "ast/visitor/ast_printer.hpp"
#include "ast/visitor/ast_serializer.hpp"
#include "check/type_checker.hpp"
#include "codegen/llvm_backend/llvm_backend.hpp"
#include "container/text_buffer.hpp"
#include "debug/log.hpp"
#include "lexer/lexer.hpp"
#include "parser/crow/crow_parser.hpp"
#include "token/token.hpp"

// Local Includes:
#include "cli_arguments.hpp"


// Enums:
enum ExitCode {
  OK = 0,
  IMPROPER_USAGE,
  EXCEPTION = 100,
  SIGNAL = 200,
};

// Functions:
auto open_file(const fs::path t_path) -> container::TextBuffer
{
  using namespace container;

  if(!fs::exists(t_path)) {
    std::stringstream ss;
    ss << "File does not exist! ";
    ss << std::quoted(t_path.string());

    throw std::invalid_argument{ss.str()};
  }

  TextBuffer tb{t_path.string()};

  std::ifstream ifs{t_path};
  while(ifs.good() && !ifs.eof()) {
    std::string line;
    std::getline(ifs, line);

    tb.add_line(std::move(line));
  }

  return tb;
}

auto lex(const fs::path& t_path) -> token::TokenStream
{
  using namespace lexer;
  using container::TextBuffer;

  DBG_PRINTLN("|> Lexing:");

  auto ts_ptr{std::make_shared<TextBuffer>(open_file(t_path))};
  Lexer lexer{ts_ptr};
  const auto tokenstream{lexer.tokenize()};

  DBG_PRINTLN("$");

  return tokenstream;
}

auto print_ast([[maybe_unused]] ast::node::NodePtr t_ast) -> void
{
  using ast::visitor::AstPrinter;

#ifdef DEBUG

  // Pretty print the AST
  DBG_PRINTLN("|> Pretty printing AST:");
  std::stringstream ss;
  ss << "\nAST:\n";

  AstPrinter printer{ss};
  printer.print(t_ast);

  DBG_INFO(ss.str());

  DBG_PRINTLN("$");
#endif // DEBUG
}

/*!
 * Print the AST as XML.
 * Printing the AST as XML allows you to inspect large AST's beter using an XML
 * viewer.
 */
auto serialize_ast([[maybe_unused]] ast::node::NodePtr t_ast) -> void
{
  using ast::visitor::AstSerializer;

#ifdef DEBUG
  DBG_PRINTLN("|> Printing the AST as XML:");

  // Serialize the AST.
  AstSerializer serializer;
  serializer.serialize(t_ast, std::cout);

  DBG_PRINTLN("$");
#endif // DEBUG
}

auto parse(const token::TokenStream& t_ts) -> ast::node::NodePtr
{
  using namespace parser::crow;

  DBG_PRINTLN("|> Parsing:");

  CrowParser parser{t_ts};
  const auto ast{parser.parse()};

  DBG_PRINTLN("$");

  return ast;
}

auto check_types(ast::node::NodePtr t_ast) -> void
{
  using namespace check;

  DBG_PRINTLN("|> Type checking:");

  TypeChecker type_checker;
  type_checker.check(t_ast);

  DBG_PRINTLN("$");
}

auto generate(ast::node::NodePtr t_ast) -> void
{
  using namespace codegen::llvm_backend;

  DBG_PRINTLN("|> Code generation:");

  LlvmBackend backend;
  backend.codegen(t_ast);
  // backend.compile("main.out");

#ifdef DEBUG
  std::stringstream ss;
  ss << "\nLLVM IR:\n";

  backend.dump_ir(ss);

  DBG_INFO(ss.str());

  DBG_PRINTLN("$");
#endif // DEBUG

  DBG_PRINTLN("$");
}

auto run() -> void
{
  using namespace container;

  for(const auto& path : settings.m_paths) {
    const auto ts{lex(path)};
    const auto ast{parse(ts)};

    print_ast(ast);
    serialize_ast(ast);

    check_types(ast);
    print_ast(ast);


    generate(ast);
  }
}

auto main(int t_argc, char* t_argv[]) -> int
{
  CLI::App app{"Compiler for Crow(lang)"};

  // TODO: Relocate?
#ifdef DEBUG
  // Do not absorb cpptrace errors on debug build.
  cpptrace::absorb_trace_exceptions(false);
#endif

  DBG_SET_LOGLEVEL(INFO);
  try {
    parse_args(app, t_argc, t_argv);
  } catch(const CLI::ParseError& e) {
    return -app.exit(e);
  }

  // Set LogLevel to verbose for now
  DBG_SET_LOGLEVEL(VERBOSE);

  try {
    run();
  } catch(std::exception& e) {
    using namespace rang;

    std::cerr << "\n";
    std::cerr << style::bold << " - ";
    std::cerr << fg::red << "EXCEPTION";
    std::cerr << fg::reset << " - \n" << style::reset;

    // Print error message:
    std::cerr << e.what() << std::flush;

    return ExitCode::EXCEPTION;
  }

  return ExitCode::OK;
}
