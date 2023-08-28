#include "return.hpp"


using namespace node::control;

using namespace visitor;

Return::Return(NodePtr&& t_expr): m_expr{std::forward<NodePtr>(t_expr)}
{}

auto Return::expr() -> NodePtr&
{
  return m_expr;
}

