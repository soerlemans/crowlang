#include "increment.hpp"


using namespace node::operators;

using namespace visitor;

// Postfix:
Increment::Increment(NodePtr&& t_left, bool t_prefix)
  : UnaryOperator{std::forward<NodePtr>(t_left)}, m_prefix{t_prefix}
{}

auto Increment::prefix() const -> bool
{
  return m_prefix;
}
