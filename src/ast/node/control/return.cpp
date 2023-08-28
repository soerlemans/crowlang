#include "return.hpp"


using namespace ast::node::control;

Return::Return(NodePtr&& t_expr): m_expr{std::move(t_expr)}
{}

auto Return::expr() -> NodePtr&
{
  return m_expr;
}
