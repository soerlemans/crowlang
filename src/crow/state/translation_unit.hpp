#ifndef CROW_CROW_STATE_TRANSLATION_UNIT_HPP
#define CROW_CROW_STATE_TRANSLATION_UNIT_HPP

// STL Includes:
#include <filesystem>
#include <iosfwd>

// Absolute Includes:
#include "crow/ast/node/fdecl.hpp"
#include "crow/codegen/backend_interface.hpp"
#include "crow/container/text_buffer.hpp"
#include "crow/semantic/symbol_table/symbol_table.hpp"
#include "crow/token/token_stream.hpp"

namespace state {
// Using Statements:
using ast::node::NodePtr;
using codegen::AstPack;
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

  path m_source_file;
  TextStreamPtr m_text_stream;
  TokenStream m_token_stream;
  NodePtr m_ast;
  SymbolTablePtr m_symbol_table;

  public:
  TranslationUnit(path t_source_file);

  //! Tokenize the text buffer.
  virtual auto lex(const TextStreamPtr& t_text_stream) -> TokenStream;

  //! Parse  the tokenized stream.
  virtual auto parse(const TokenStream& t_token_stream) -> NodePtr;

  //! Print the AST, only available if @ref DEBUG is defined.
  virtual auto print_ast(NodePtr t_ast) const -> void;

  //! Analyse the semantic validaty of the AST.
  virtual auto semantic(NodePtr t_ast) -> SymbolTablePtr;

  //! Execute the codegeneration backend.
  virtual auto backend(AstPack t_pack) -> void;

  //! Crow compiler regular compilation flow.
  virtual auto execute() -> void;

  virtual ~TranslationUnit() = default;
};
} // namespace state

auto operator<<(std::ostream& t_os, state::TranslationUnitPhase t_phase)
  -> std::ostream&;
auto operator<<(std::ostream& t_os, state::TranslationUnit t_unit)
  -> std::ostream&;

#endif // CROW_CROW_STATE_TRANSLATION_UNIT_HPP
