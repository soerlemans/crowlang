#ifndef STATE_HPP
#define STATE_HPP

// Absolute Includes:
#include "container/text_buffer.hpp"
#include "crow/ast/node/fdecl.hpp"
#include "crow/check/symbol_table/symbol_table.hpp"
#include "crow/token/token_stream.hpp"

namespace state {
// Using Statements:
using ast::node::NodePtr;
using check::symbol_table::SymbolTablePtr;
using container::TextStreamPtr;
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

  //! Check the semantic validaty of the AST.
  auto check_semantics() -> void;

  //! Execute the codegeneration backend.
  auto backend() -> void;

  //! Crow compiler regular compilation flow.
  auto compile() -> void;

  virtual ~TranslationUnit() = default;
};
} // namespace state

#endif // STATE_HPP
