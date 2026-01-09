#ifndef CROW_CROW_PARSER_CROW_PRATT_BINDING_BINDING_MAP_HPP
#define CROW_CROW_PARSER_CROW_PRATT_BINDING_BINDING_MAP_HPP

// STL Includes:
#include <unordered_map>
#include <utility>

// Absolute Includes:
#include "crow/token/token_type.hpp"

// Macros:
//! Convenience macro so we can omit the @ref TokenType prefix
#define INSERT_BINDING(t_type, t_lbp, t_rbp) \
  insert_binding(TokenType::t_type, t_lbp, t_rbp);

namespace parser::pratt::binding {
// Using Statements:
using token::TokenType;

// Aliases:
//! Two integers are used to indicate the binding power.
using BindingPower = std::pair<int, int>;

//! Internal type used to map tokens to their @ref BindingPower.
using TokenBindingMap = std::unordered_map<TokenType, BindingPower>;

// Classes:
//! Binding map contains the precedence bindings for tokens.
class BindingMap {
  private:
  TokenBindingMap m_map;

  protected:
  //! Constructor is protected, to disallow direct usage.
  BindingMap() = default;

  auto insert_binding(TokenType t_type, int t_lbp, int t_rbp) -> void;

  public:
  auto at(TokenType t_type) const -> BindingPower;
  auto rbp(TokenType t_type) const -> int;
  auto lbp(TokenType t_type) const -> int;

  virtual ~BindingMap() = default;
};
} // namespace parser::pratt::binding


#endif // CROW_CROW_PARSER_CROW_PRATT_BINDING_BINDING_MAP_HPP
