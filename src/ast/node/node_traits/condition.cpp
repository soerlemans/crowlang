#include "condition.hpp"


using namespace ast::node::node_traits;

Condition::Condition(NodePtr&& t_condition): m_condition{std::move(t_condition)}
{}

auto Condition::condition() -> NodePtr&
{
  return m_condition;
}
