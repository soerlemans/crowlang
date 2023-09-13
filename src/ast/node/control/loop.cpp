#include "loop.hpp"


using namespace ast::node::control;
using namespace ast::node::node_traits;

Loop::Loop(NodePtr&& t_init, NodePtr&& t_condition, NodePtr&& t_expr,
           NodeListPtr&& t_body)
  : Init{std::move(t_init)},
    Condition{std::move(t_condition)},
    Body{std::move(t_body)},
    m_expr{std::move(t_expr)}

{}

auto Loop::expr() -> NodePtr&
{
  return m_expr;
}
