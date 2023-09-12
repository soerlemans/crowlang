#include "dot_expr.hpp"


using namespace ast::node::lvalue;

DotExpr::DotExpr(std::string_view t_identifier, NodePtr&& t_expr)
  : m_identifier{std::move(t_identifier)}, m_expr{std::move(t_expr)}
{}

auto DotExpr::identifier() const -> std::string_view
{
  return m_identifier;
}

auto DotExpr::expr() -> NodePtr&
{
  return m_expr;
}
