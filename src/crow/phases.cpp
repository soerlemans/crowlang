#include "phases.hpp"

// Using Declarations:
using std::filesystem::path;

// Internal Functions:
namespace {
// TODO: Move to /lib with crow/container.
auto read_file(const path t_path) -> container::TextBuffer
{
  using container::TextBuffer;
  using std::filesystem::exists;

  if(!exists(t_path)) {
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
} // namespace

// Functions:
auto lex(const path& t_path) -> token::TokenStream
{
  using container::TextBuffer;
  using lexer::Lexer;

  DBG_PRINTLN("<lexing>");

  const auto stream_ptr{std::make_shared<TextBuffer>(read_file(t_path))};
  const auto tokenstream{lex(stream_ptr)};

  DBG_PRINTLN("</lexing>");

  return tokenstream;
}

auto lex(const container::TextStreamPtr& t_stream) -> token::TokenStream
{
  using container::TextBuffer;
  using lexer::Lexer;

  DBG_PRINTLN("<lexing>");

  Lexer lexer{t_stream};
  const auto tokenstream{lexer.tokenize()};

  DBG_PRINTLN("</lexing>");

  return tokenstream;
}

auto parse(const token::TokenStream& t_ts) -> ast::node::NodePtr
{
  using parser::crow::CrowParser;

  DBG_PRINTLN("<parsing>");

  CrowParser parser{t_ts};
  const auto ast{parser.parse()};

  DBG_PRINTLN("</parsing>");

  return ast;
}

auto print_ast([[maybe_unused]] ast::node::NodePtr t_ast) -> void
{
  using ast::visitor::AstPrinter;

#ifdef DEBUG

  // Pretty print the AST
  DBG_PRINTLN("<print_ast>");
  std::stringstream ss;
  ss << "\nAST:\n";

  AstPrinter printer{ss};
  printer.print(t_ast);

  DBG_INFO(ss.str());

  DBG_PRINTLN("</print_ast>");
#endif // DEBUG
}

auto check_types(ast::node::NodePtr t_ast) -> void
{
  using check::TypeChecker;

  DBG_PRINTLN("<type_checking>");

  TypeChecker type_checker;
  type_checker.check(t_ast);

  DBG_PRINTLN("</type_checking>");
}

auto backend(ast::node::NodePtr t_ast) -> void
{
  using codegen::cpp_backend::CppBackend;

  DBG_PRINTLN("<codegen>");

  CppBackend backend;
  backend.compile(t_ast);

  DBG_PRINTLN("</codegen>");
}

auto run() -> void
{
  for(const auto& path : settings.m_paths) {
    const auto ts{lex(path)};
    DBG_PRINTLN("TokenStream: ", ts);

    const auto ast{parse(ts)};

    print_ast(ast);

    check_types(ast);
    print_ast(ast);

    backend(ast);
  }
}
