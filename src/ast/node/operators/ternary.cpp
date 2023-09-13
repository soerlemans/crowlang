#include "ternary.hpp"


using namespace ast::node::operators;
using namespace ast::node::node_traits;

Ternary::Ternary(NodePtr&& t_condition, NodePtr&& t_then, NodePtr&& t_alt)
  : Condition{std::move(t_condition)},
    m_then{std::move(t_then)},
    m_alt{std::move(t_alt)}
{}

auto Ternary::then() -> NodePtr&
{
  return m_then;
}

auto Ternary::alt() -> NodePtr&
{
  return m_alt;
}
