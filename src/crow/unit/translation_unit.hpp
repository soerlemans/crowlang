#ifndef CROW_CROW_UNIT_TRANSLATION_UNIT_HPP
#define CROW_CROW_UNIT_TRANSLATION_UNIT_HPP

// STL Includes:
#include <filesystem>
#include <iosfwd>

// Absolute Includes:
#include "crow/ast/node/fdecl.hpp"
#include "crow/codegen/backend_interface.hpp"
#include "crow/container/text_buffer.hpp"
#include "crow/semantic/symbol_table/symbol_table.hpp"
#include "crow/token/token_stream.hpp"
#include "crow/unit/build_unit.hpp"

namespace unit {
// Using Statements:
using ast::node::NodePtr;
using codegen::CompileParams;
using container::TextStreamPtr;
using semantic::symbol_table::SymbolTablePtr;
using std::filesystem::path;
using token::TokenStream;

// Enums:
/*!
 * Enumeration keeping track of the current phase of processing.
 * The @ref TranslationUnit is in.
 */
enum class TranslationUnitPhase {
  IDLE,
  LEXING,
  PARSING,
  SEMANTIC_ANALYSIS,
  CODE_GENERATION,
  COMPLETED,
  FAILED
};

// Classes:
// TODO: Maybe use the State or Command pattern?
// We could possibly also have ModuleUnit or ConfigurationUnit?
// And these would need to be processed.
/*!
 * Keeps track of all relevant data within a single translation unit.
 * Invokes all the steps needed to go from source code to a compiled binary.
 * For now each @ref TranslationUnit references on source file.
 */
class TranslationUnit {
  private:
  TranslationUnitPhase m_phase;

  // Config:
  BuildUnitPtr m_build_unit;

  // Data:
  path m_source_file;
  TextStreamPtr m_text_stream;
  TokenStream m_token_stream;
  NodePtr m_ast;
  SymbolTablePtr m_symbol_table;

  public:
  TranslationUnit(BuildUnitPtr t_build_unit, path t_source_file);

  //! Tokenize the text buffer.
  virtual auto lex(const TextStreamPtr& t_text_stream) -> TokenStream;

  //! Parse  the tokenized stream.
  virtual auto parse(const TokenStream& t_token_stream) -> NodePtr;

  //! Print the AST, only available if @ref DEBUG is defined.
  virtual auto print_ast(NodePtr t_ast) const -> void;

  //! Analyse the semantics of the AST.
  virtual auto semantic(NodePtr t_ast) -> SymbolTablePtr;

  //! Execute the codegeneration backend.
  virtual auto backend(CompileParams& t_params) -> void;

  //! Crow compiler regular compilation flow.
  virtual auto execute() -> void;

  virtual ~TranslationUnit() = default;
};
} // namespace unit

auto operator<<(std::ostream& t_os, unit::TranslationUnitPhase t_phase)
  -> std::ostream&;
auto operator<<(std::ostream& t_os, unit::TranslationUnit t_unit)
  -> std::ostream&;

#endif // CROW_CROW_UNIT_TRANSLATION_UNIT_HPP
