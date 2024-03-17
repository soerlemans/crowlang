#ifndef CROW_PARSER_PRATT_BINDING_BINDING_MAP_HPP
#define CROW_PARSER_PRATT_BINDING_BINDING_MAP_HPP

// STL Includes:
#include <unordered_map>
#include <utility>

// Includes:
#include "../../../token/token_type.hpp"

namespace parser::pratt::binding {
// Macros:
//! Convenience macro so we can omit the TokenType prefix
#define INSERT_BINDING(t_type, t_lbp, t_rbp) \
  insert_binding(token::TokenType::t_type, t_lbp, t_rbp);

// Using Statements:
using token::TokenType;

// Aliases:
//! Two integers are used to indicate the binding power
using BindingPower = std::pair<int, int>;

// Classes:
// TODO: Make std::unordered_map a member and not a parent.
//! Binding map contains the precedence bindings.
class BindingMap : public std::unordered_map<TokenType, BindingPower> {
  protected:
  //! Constructor is protected, to disallow direct usage
  BindingMap() = default;

  auto insert_binding(TokenType t_type, int t_lbp, int t_rbp) -> void;

  public:
  auto rbp(TokenType t_type) const -> int;
  auto lbp(TokenType t_type) const -> int;

  virtual ~BindingMap() = default;
};
} // namespace parser::pratt::binding


#endif // CROW_PARSER_PRATT_BINDING_BINDING_MAP_HPP
