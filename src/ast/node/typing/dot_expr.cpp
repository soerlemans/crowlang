#include "dot_expr.hpp"


using namespace ast::node::lvalue;
using namespace ast::node::node_traits;

DotExpr::DotExpr(const std::string_view t_identifier, NodePtr&& t_expr)
  : Identifier{t_identifier}, m_expr{std::move(t_expr)}
{}

auto DotExpr::expr() -> NodePtr&
{
  return m_expr;
}
