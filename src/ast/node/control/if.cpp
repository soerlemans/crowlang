#include "if.hpp"


using namespace ast::node::control;
using namespace ast::node::node_traits;

If::If(NodePtr&& t_init, NodePtr&& t_condition, NodeListPtr&& t_then,
       NodeListPtr&& t_alt)
  : InitExpr{std::move(t_init)},
    Condition{std::move(t_condition)},
    m_then{std::move(t_then)},
    m_alt{std::move(t_alt)}
{}

auto If::then() -> NodeListPtr&
{
  return m_then;
}

auto If::alt() -> NodeListPtr&
{
  return m_alt;
}
