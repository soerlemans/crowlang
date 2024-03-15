#include "then.hpp"

namespace ast::node::node_traits {
// Methods:
Then::Then(NodePtr&& t_then): m_then{std::move(t_then)}
{}

auto Then::then() -> NodePtr&
{
  return m_then;
}
} // namespace ast::node::node_traits
