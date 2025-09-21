#ifndef CROW_CROW_SEMANTIC_TYPE_REGISTER_HPP
#define CROW_CROW_SEMANTIC_TYPE_REGISTER_HPP

// Absolute includes:
#include "crow/container/text_position.hpp"
#include "crow/types/semantic/symbol.hpp"

// Local Includes:
#include "symbol_env_state.hpp"
#include "type_promoter.hpp"

namespace semantic {
// Using:
using symbol::SymbolData;

// Classes:
/*!
 * This class is responsible.
 * For cleanly validating the semantic validity of various expressions.
 * Its meant for a cleaner separation of concerns from @ref SemanticChecker.
 */
class SemanticValidator {
  private:
  SymbolEnvState m_symbol_state;
  TypePromoter m_type_promoter;

  private:
  auto error();

  public:
  auto register_struct() -> SymbolData;
  auto register_alias() -> SymbolData;

  auto validate_function() -> SymbolData;
  auto validate_method() -> SymbolData;

  auto validate_decl_expr() -> SymbolData;

  auto validate_unary_prefix() -> SymbolData;

  //! Validate logical `not`.
  auto validate_logical_unop() -> SymbolData;

  //! Validate logical `and` and `or`.
  auto validate_logical_binop() -> SymbolData;

  auto validate_arithmetic() -> SymbolData;
  auto validate_assignment() -> SymbolData;
  auto validate_comparison() -> SymbolData;
};

} // namespace semantic

#endif // CROW_CROW_SEMANTIC_TYPE_REGISTER_HPP
