// STL Includes:
#include <CLI/Error.hpp>
#include <filesystem>
#include <fstream>

// Library Includes:
#include <CLI/App.hpp>
#include <CLI/CLI.hpp>
#include <CLI/Validators.hpp>
#include <rang.hpp>

// Includes:
#include "ast/node/fdecl.hpp"
#include "ast/node/include.hpp"
#include "ast/visitor/print_visitor.hpp"
#include "codegen/llvm_backend/llvm_backend.hpp"
#include "container/text_buffer.hpp"
#include "debug/log.hpp"
#include "debug/log_macros.hpp"
#include "lexer/lexer.hpp"
#include "parser/crow/crow_parser.hpp"
#include "token/token.hpp"
#include "typing/type_checker.hpp"

// Local Includes:
#include "banner.hpp"
#include "version.hpp"


// Aliases:
namespace fs = std::filesystem;

// Enums:
enum ExitCode {
  OK = 0,
  IMPROPER_USAGE,
  EXCEPTION = 100,
  SIGNAL = 200,
};

// Globals:
struct Settings {
  std::vector<fs::path> m_paths;
} settings;

// Functions:
auto parse_args(CLI::App& t_app, const int t_argc, char* t_argv[]) -> void
{
  t_app.failure_message(CLI::FailureMessage::help);

  // Program files
  t_app.add_option("{}", settings.m_paths, "Postional arguments")
    ->check(CLI::ExistingFile);

  // Version flag
  std::stringstream ss;
  ss << "Version: " << CROW_VERSION;
  t_app.set_version_flag("-v,--version", ss.str(), "Show compiler version");

  t_app.parse(t_argc, t_argv);
}

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

  DBG_PRINTLN("|> Lexing:");

  auto ts_ptr{std::make_shared<TextBuffer>(open_file(t_path))};
  Lexer lexer{ts_ptr};
  const auto tokenstream{lexer.tokenize()};

  DBG_PRINTLN("$");

  return tokenstream;
}

auto pprint([[maybe_unused]] ast::node::NodePtr t_ast) -> void
{
  using namespace ast::visitor;

  // Pretty print the AST
#if DEBUG
  DBG_PRINTLN("|> Pretty printing AST:");
  std::stringstream ss;
  ss << "\nAst:\n";
  PrintVisitor pprint{ss};
  pprint.traverse(t_ast);

  DBG_INFO(ss.str());

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
  using namespace typing;

  DBG_PRINTLN("|> Type checking:");

  TypeChecker type_checker;
  type_checker.traverse(t_ast);

  DBG_PRINTLN("$");
}

auto generate(ast::node::NodePtr t_ast) -> void
{
  using namespace codegen::llvm_backend;

  DBG_PRINTLN("|> Code generation:");

  LlvmBackend backend;
  backend.codegen(t_ast);
  // backend.compile("main.out");

#if DEBUG
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

    pprint(ast);

    check_types(ast);
    generate(ast);
  }
}

auto main(int t_argc, char* t_argv[]) -> int
{
	print_banner();

  CLI::App app{"Compiler for Crow(lang)"};

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
    std::cerr << e.what() << std::endl;

    return ExitCode::EXCEPTION;
  }

  return ExitCode::OK;
}
