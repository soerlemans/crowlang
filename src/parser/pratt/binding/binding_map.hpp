#ifndef AWX_PARSER_PRATT_BINDING_BINDING_MAP_HPP
#define AWX_PARSER_PRATT_BINDING_BINDING_MAP_HPP

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

// Aliases:
//! Two integers are used to indicate the binding power
using BindingPower = std::pair<int, int>;

// Classes:
//! Binding map contains the precedence bindings
class BindingMap : public std::unordered_map<token::TokenType, BindingPower> {
  protected:
  //! Constructor is protected, to disallow direct usage
  BindingMap() = default;

  auto insert_binding(token::TokenType t_type, int t_lbp, int t_rbp) -> void;

  public:
  auto rbp(token::TokenType t_type) const -> int;
  auto lbp(token::TokenType t_type) const -> int;

  virtual ~BindingMap() = default;
};
} // namespace parser::pratt::binding


#endif // AWX_PARSER_PRATT_BINDING_BINDING_MAP_HPP
