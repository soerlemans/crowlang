#include "expr.hpp"

namespace ast::node::node_traits {
// Methods:
Expr::Expr(NodePtr&& t_expr): m_expr{std::move(t_expr)}
{}

auto Expr::expr() -> NodePtr&
{
  return m_expr;
}
} // namespace ast::node::node_traits
