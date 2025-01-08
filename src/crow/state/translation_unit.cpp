#include "translation_unit.hpp"

namespace state {

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

  TextBuffer text_buffer{t_path.string()};

  std::ifstream ifs{t_path};
  while(ifs.good() && !ifs.eof()) {
    std::string line;
    std::getline(ifs, line);

    text_buffer.add_line(std::move(line));
  }

  return text_buffer;
}
} // namespace

// Functions:
auto TranslationUnit::lex() -> void
{
  using lexer::Lexer;

  m_phase = Phase::LEXING;

  DBG_PRINTLN("<lexing>");

  Lexer lexer{t_state.m_text_stream};
  m_token_stream = lexer.tokenize();

  DBG_PRINTLN("</lexing>");
}

auto parse(State& t_state) -> void
{
  using parser::crow::CrowParser;

  m_phase = Phase::PARSING;

  DBG_PRINTLN("<parsing>");

  CrowParser parser{m_token_stream};
  m_ast = parser.parse();

  DBG_PRINTLN("</parsing>");

  return ast;
}

auto print_ast() -> void
{
  using ast::visitor::AstPrinter;

#ifdef DEBUG
  // Pretty print the AST
  DBG_PRINTLN("<print_ast>");
  std::stringstream ss;
  ss << "\nAST:\n";

  AstPrinter printer{ss};
  printer.print(m_ast);

  DBG_INFO(ss.str());

  DBG_PRINTLN("</print_ast>");
#endif // DEBUG
}

auto check_semantics() -> void
{
  using check::SemanticChecker;

  DBG_PRINTLN("<semantic_checking>");

  // Check the semantics of the written program.
  SemanticChecker checker;
  const auto pack{checker.check(m_ast)};

  DBG_PRINTLN("</semantic_checking>");
}

auto backend() -> void
{
  using codegen::cpp_backend::CppBackend;

  DBG_PRINTLN("<codegen>");

  CppBackend backend;
  backend.compile(m_ast, t_path.stem());

  DBG_PRINTLN("</codegen>");
}

auto run() -> void
{
  for(const auto& path : settings.m_paths) {
    const auto ts{lex(path)};
    DBG_PRINTLN("TokenStream: ", ts);

    const auto ast{parse(ts)};
    print_ast(ast);

    const auto pack{check_semantics(ast)};
    print_ast(ast);

    // TODO: Forward SemanticPack to this.
    backend(pack, path);
  }
}
} // namespace state
