#include "expr.hpp"


using namespace ast::node::node_traits;

Expr::Expr(NodePtr&& t_expr): m_expr{std::move(t_expr)}
{}

auto Expr::expr() -> NodePtr&
{
  return m_expr;
}
