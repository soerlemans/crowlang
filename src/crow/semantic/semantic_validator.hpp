#ifndef CROW_CROW_SEMANTIC_SEMANTIC_VALIDATOR_HPP
#define CROW_CROW_SEMANTIC_SEMANTIC_VALIDATOR_HPP

// STL Includes:
#include <optional>

// Absolute Includes:
#include "crow/container/text_position.hpp"
#include "crow/types/semantic/symbol.hpp"

// Local Includes:
#include "symbol_env_state.hpp"
#include "type_promoter.hpp"

namespace semantic {
// Using:
using container::TextPosition;
using symbol::SymbolData;

// Aliases:
using SymbolDataOpt = std::optional<SymbolData>;

// Enums:
// enum class BindingExprType {
// 	TYPE
// };

// Structs:
struct BindingExprData {
  SymbolDataOpt m_init_expr;
  std::string m_identifier;
  SymbolDataOpt m_type;
  TextPosition m_position;
};

struct UnaryOperationData {
  SymbolData m_lhs;
  TextPosition m_position;
};

struct BinaryOperationData {
  SymbolData m_lhs;
  SymbolData m_rhs;
  TextPosition m_position;
};

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

  protected:
  // auto error();

  // Environment related methods:
  auto push_env() -> void;
  auto pop_env() -> void;
  auto clear_env() -> void;

  auto add_symbol_declaration(std::string_view t_id, const SymbolData& t_data)
    -> void;

  /*!
   * Add symbol to current @ref EnvSate.
   * Also add the symbol to the global @ref SymbolTable.
   *
   * @return false means inserting the symbol failed.
   */
  auto add_symbol_definition(std::string_view t_id, const SymbolData& t_data)
    -> void;

  [[nodiscard("Pure method must use result.")]]
  auto get_symbol_data_from_env(std::string_view t_id) const -> SymbolData;

  auto handle_condition(const SymbolData& t_data,
                        const TextPosition& t_pos) const -> void;

  //! Handle type promotion between two different types.
  auto promote(const SymbolData& t_lhs, const SymbolData& rhs,
               PromotionMode t_mode = PromotionMode::PROMOTE_TO_LHS) const
    -> NativeTypeOpt;

  public:
  SemanticValidator() = default;

  auto register_struct() -> SymbolData;
  auto register_alias() -> SymbolData;

  auto validate_function() -> SymbolData;
  auto validate_method() -> SymbolData;

  auto validate_binding_expr(const BindingExprData& t_data) -> SymbolData;

  auto validate_unary_prefix() -> SymbolData;

  //! Validate logical `not`.
  auto validate_logical_unop(const UnaryOperationData& t_data) -> SymbolData;

  //! Validate logical `and` and `or`.
  auto validate_logical_binop(const BinaryOperationData& t_data) -> SymbolData;

  auto validate_arithmetic(const BinaryOperationData& t_data) -> SymbolData;
  auto validate_assignment(const BinaryOperationData& t_data) -> SymbolData;
  auto validate_comparison(const BinaryOperationData& t_data) -> SymbolData;

  virtual ~SemanticValidator() = default;
};
} // namespace semantic

#endif // CROW_CROW_SEMANTIC_SEMANTIC_VALIDATOR_HPP
