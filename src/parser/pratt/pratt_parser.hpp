#ifndef CROW_PARSER_PRATT_PRATT_PARSER_HPP
#define CROW_PARSER_PRATT_PRATT_PARSER_HPP

// STL Includes:
#include <unordered_map>
#include <utility>

// Includes:
#include "../../types.hpp"
#include "../parser.hpp"
#include "binding/maps.hpp"


namespace parser::pratt {
// Aliases:
//! This type is used to get the right hand side of a binary expressions
using PrattFunc = std::function<n::NodePtr(token::TokenType)>;
//! This type takes the binding power
using BpFunc = std::function<n::NodePtr(int)>;
//! This type is used to parse extra infix operations of a universal method
using InfixFunc = std::function<n::NodePtr(n::NodePtr&, const PrattFunc&)>;

// Classes:
class PrattParser : public Parser {
  private:
  // Note that these come from a submodule
  binding::PrefixMap m_prefix;
  binding::InfixMap m_infix;
  binding::PostfixMap m_postfix;

  public:
  PrattParser(token::TokenStream&& t_tokenstream);

  // Prefix parsing:
  virtual auto lvalue() -> n::NodePtr;
  virtual auto literal() -> n::NodePtr;
  virtual auto grouping() -> n::NodePtr;
  virtual auto unary_prefix(const PrattFunc& t_fn) -> n::NodePtr;
  virtual auto negation(const PrattFunc& t_expr) -> n::NodePtr;
  virtual auto precrement() -> n::NodePtr;
  virtual auto function_call() -> n::NodePtr;

  virtual auto prefix(const PrattFunc& t_fn) -> n::NodePtr;

  // Infix parsing:
  virtual auto infix_rhs(token::TokenType t_type) -> n::NodePtr;
  virtual auto arithmetic(n::NodePtr& t_lhs, const PrattFunc& t_fn)
    -> n::NodePtr;
  virtual auto logical(n::NodePtr& t_lhs, const PrattFunc& t_fn) -> n::NodePtr;
  virtual auto assignment(n::NodePtr& t_lhs, const PrattFunc& t_fn)
    -> n::NodePtr;
  virtual auto comparison(n::NodePtr& t_lhs, const PrattFunc& t_fn)
    -> n::NodePtr;

  virtual auto infix(n::NodePtr& t_lhs, const PrattFunc& t_fn) -> n::NodePtr;

  // Grammar:
  virtual auto newline_opt() -> void = 0;

  // Expressions:
  virtual auto expr(int t_min_bp = 0) -> n::NodePtr;

  // virtual auto multiple_expr_list() -> n::NodeListPtr = 0;
  // virtual auto expr_list() -> n::NodeListPtr = 0;
  virtual auto expr_list_opt() -> n::NodeListPtr = 0;

  ~PrattParser() override = default;
};
} // namespace parser::pratt

#endif // CROW_PARSER_PRATT_PRATT_PARSER_HPP
