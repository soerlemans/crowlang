#include "condition.hpp"

namespace ast::node::node_traits {
// Methods:
Condition::Condition(NodePtr&& t_condition): m_condition{std::move(t_condition)}
{}

auto Condition::condition() -> NodePtr&
{
  return m_condition;
}
} // namespace ast::node::node_traits
