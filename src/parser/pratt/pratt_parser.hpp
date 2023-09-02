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
using PrattFunc = std::function<ast::node::NodePtr(token::TokenType)>;
//! This type takes the binding power
using BpFunc = std::function<ast::node::NodePtr(int)>;
//! This type is used to parse extra infix operations of a universal method
using InfixFunc =
  std::function<ast::node::NodePtr(ast::node::NodePtr&, const PrattFunc&)>;

// Classes:
class PrattParser : public Parser {
  private:
  // Note that these come from a submodule
  binding::PrefixMap m_prefix;
  binding::InfixMap m_infix;
  binding::PostfixMap m_postfix;

  public:
  PrattParser(token::TokenStream&& t_tokenstream);

  // Expression terminals:
  virtual auto unary_prefix(const PrattFunc& t_fn) -> ast::node::NodePtr;
  virtual auto grouping() -> ast::node::NodePtr;
  virtual auto negation(const PrattFunc& t_expr) -> ast::node::NodePtr;
  virtual auto literal() -> ast::node::NodePtr;
  virtual auto lvalue() -> ast::node::NodePtr;

  virtual auto precrement() -> ast::node::NodePtr;

  virtual auto function_call() -> ast::node::NodePtr;

  // Infix parsing:
  virtual auto arithmetic(ast::node::NodePtr& t_lhs, const PrattFunc& t_fn)
    -> ast::node::NodePtr;
  virtual auto logical(ast::node::NodePtr& t_lhs, const PrattFunc& t_fn)
    -> ast::node::NodePtr;
  virtual auto assignment(ast::node::NodePtr& t_lhs, const PrattFunc& t_fn)
    -> ast::node::NodePtr;
  virtual auto comparison(ast::node::NodePtr& t_lhs, const PrattFunc& t_fn)
    -> ast::node::NodePtr;

  virtual auto infix(ast::node::NodePtr& t_lhs, const PrattFunc& t_fn)
    -> ast::node::NodePtr;

  // Grammar:
  virtual auto newline_opt() -> void = 0;

  // Expressions:
  virtual auto expr(int t_min_bp = 0) -> ast::node::NodePtr;

  // virtual auto multiple_expr_list() -> ast::node::NodeListPtr = 0;
  // virtual auto expr_list() -> ast::node::NodeListPtr = 0;
  virtual auto expr_list_opt() -> ast::node::NodeListPtr = 0;

  ~PrattParser() override = default;
};
} // namespace parser::pratt

#endif // CROW_PARSER_PRATT_PRATT_PARSER_HPP
