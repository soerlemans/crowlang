#include "increment.hpp"


using namespace ast::node::operators;

Increment::Increment(NodePtr&& t_left, bool t_prefix)
  : UnaryOperator{std::move(t_left)}, m_prefix{t_prefix}
{}

auto Increment::prefix() const -> bool
{
  return m_prefix;
}
