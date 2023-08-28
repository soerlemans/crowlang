#include "decrement.hpp"


using namespace node::operators;

using namespace visitor;

Decrement::Decrement(NodePtr&& t_left, bool t_prefix)
  : UnaryOperator{std::forward<NodePtr>(t_left)}, m_prefix{t_prefix}
{}

auto Decrement::prefix() const -> bool
{
  return m_prefix;
}
