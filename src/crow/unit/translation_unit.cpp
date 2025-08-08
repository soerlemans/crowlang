#include "translation_unit.hpp"

// STL Includes:
#include <fstream>
#include <iostream>

// Absolute Includes:
#include "crow/ast/node/fdecl.hpp"
#include "crow/ast/visitor/ast_printer.hpp"
#include "crow/codegen/backend_interface.hpp"
#include "crow/lexer/lexer.hpp"
#include "crow/mir/mir_builder/mir_builder.hpp"
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

namespace unit {
// Methods:
TranslationUnit::TranslationUnit(BuildUnitPtr t_build_unit,
                                 const path t_source_file)
  : m_build_unit{std::move(t_build_unit)},
    m_source_file{t_source_file},
    m_text_stream{},
    m_token_stream{},
    m_ast{},
    m_mir{}
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

auto TranslationUnit::semantic(NodePtr t_ast) -> void
{
  using semantic::SemanticChecker;

  m_phase = TranslationUnitPhase::SEMANTIC_ANALYSIS;

  DBG_PRINTLN("<semantic>");

  // Temp:
  using symbol_table::node_frame::NodeFrameFactory;
  NodeFrameFactory factory{};

  // Check the semantics of the written program.
  SemanticChecker checker{};
  checker.check(t_ast);

  // DBG_INFO(symbol_table);

  DBG_PRINTLN("</semantic>");
}

auto TranslationUnit::mir(NodePtr t_ast) -> ModulePtr
{
  using mir::mir_builder::MirBuilder;

  m_phase = TranslationUnitPhase::MIR_GENERATION;

  DBG_PRINTLN("<ir_generation>");

  // Check the semantics of the written program.
  MirBuilder builder{};
  // const auto module_ptr{builder.translate(t_ast)};
  ModulePtr module_ptr{};

  if(module_ptr) {
    DBG_INFO("CLIR Module: ", module_ptr->m_name);
    DBG_PRINTLN(module_ptr);
  } else {
    // TODO: Throw?
  }

  DBG_PRINTLN("</ir_generation>");

  return module_ptr;
}

auto TranslationUnit::backend(CompileParams& t_params) -> void
{
  using codegen::BackendPtr;
  using codegen::BackendType;

  m_phase = TranslationUnitPhase::CODE_GENERATION;
  const auto stem{m_source_file.stem()};

  DBG_PRINTLN("<code_generation>");

  // Invoke build unit to build.
  m_build_unit->compile(t_params);

  DBG_PRINTLN("</code_generation>");
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

  semantic(m_ast);
  print_ast(m_ast);

  // Perform Ir generation:
  m_mir = mir(m_ast);

  // Perform compilation:
  const auto build_dir{m_build_unit->build_dir()};
  CompileParams params{m_ast, m_mir, build_dir, m_source_file};
  backend(params);
}
} // namespace unit
