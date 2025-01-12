#include "translation_unit.hpp"

// STL Includes:
#include <fstream>
#include <iostream>

// Absolute Includes:
#include "crow/ast/node/fdecl.hpp"
#include "crow/ast/visitor/ast_printer.hpp"
#include "crow/codegen/cpp_backend/cpp_backend.hpp"
#include "crow/lexer/lexer.hpp"
#include "crow/parser/crow/crow_parser.hpp"
#include "crow/semantic/semantic_checker.hpp"

// Internal Functions:
namespace {
// Using Statements:
using container::TextBuffer;
using std::filesystem::path;

// TODO: Move to /lib with crow/container.
auto read_file(const path t_path) -> TextBuffer
{
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

namespace state {
// Methods:
TranslationUnit::TranslationUnit(const path t_source_file)
  : m_source_file{t_source_file}
{}

auto TranslationUnit::lex(const TextStreamPtr& t_text_stream) -> TokenStream
{
  using lexer::Lexer;

  m_phase = TranslationUnitPhase::LEXING;

  DBG_PRINTLN("<lexing>");

  Lexer lexer{t_text_stream};
  const auto token_stream{lexer.tokenize()};

  DBG_PRINTLN("</lexing>");

  return token_stream;
}

auto TranslationUnit::parse(const TokenStream& t_token_stream) -> NodePtr
{
  using parser::crow::CrowParser;

  m_phase = TranslationUnitPhase::PARSING;

  DBG_PRINTLN("<parsing>");

  CrowParser parser{t_token_stream};
  const auto ast{parser.parse()};

  DBG_PRINTLN("</parsing>");

  return ast;
}

auto TranslationUnit::print_ast([[maybe_unused]] const NodePtr t_ast) const
  -> void
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

auto TranslationUnit::semantic(NodePtr t_ast) -> SymbolTablePtr
{
  using semantic::SemanticChecker;

  m_phase = TranslationUnitPhase::SEMANTIC_ANALYSIS;

  DBG_PRINTLN("<semantic>");

  // Check the semantics of the written program.
  SemanticChecker checker;
  const auto symbol_table{checker.check(t_ast)};

  DBG_PRINTLN("</semantic>");

  return symbol_table;
}

auto TranslationUnit::backend(const AstPack t_pack) -> void
{
  using codegen::cpp_backend::CppBackend;

  m_phase = TranslationUnitPhase::CODE_GENERATION;
  const auto stem{m_source_file.stem()};

  DBG_PRINTLN("<codegen>");

  CppBackend backend;
  backend.compile(t_pack, stem);

  DBG_PRINTLN("</codegen>");
}

auto TranslationUnit::execute() -> void
{
  using container::TextBuffer;

  m_text_stream = std::make_shared<TextBuffer>(read_file(m_source_file));

  // TODO: Fix operator= for Stream..
  // m_token_stream = lex(m_text_stream);
  const auto ts{lex(m_text_stream)};
  m_ast = parse(ts);
  print_ast(m_ast);

  m_symbol_table = semantic(m_ast);
  print_ast(m_ast);

  backend({m_ast, m_symbol_table});
}
} // namespace state
