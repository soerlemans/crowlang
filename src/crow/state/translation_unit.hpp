#ifndef STATE_HPP
#define STATE_HPP

// STL Includes:
#include <iosfwd>

// Absolute Includes:
#include "container/text_buffer.hpp"
#include "crow/ast/node/fdecl.hpp"
#include "crow/check/symbol_table/symbol_table.hpp"
#include "crow/token/token_stream.hpp"

namespace state {
// Using Statements:
using ast::node::NodePtr;
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
  LEXING,
  PARSING,
  SEMANTIC_ANALYSIS,
  CODE_GENERATION
};

// Classes:
// TODO: Maybe use the State or Command pattern?
// We could possibly also have ModuleUnit or ConfigurationUnit?
// And these would need to be processed.
/*!
 *
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
  TranslationUnit() = default;

  // Functions:
  //! Tokenize the text buffer.
  auto lex() -> void;

  //! Parse  the tokenized stream.
  auto parse() -> void;

  //! Print the AST, only available if @ref DEBUG is defined.
  auto print_ast() -> void;

  //! Analyse the semantic validaty of the AST.
  auto semantic() -> void;

  //! Execute the codegeneration backend.
  auto backend() -> void;

  //! Crow compiler regular compilation flow.
  auto compile() -> void;

  virtual ~TranslationUnit() = default;
};
} // namespace state

auto operator<<(std::ostream& t_os, state::TranslationUnitPhase t_phase)
  -> std::ostream&;
auto operator<<(std::ostream& t_os, state::TranslationUnit t_unit)
  -> std::ostream&;

#endif // STATE_HPP
