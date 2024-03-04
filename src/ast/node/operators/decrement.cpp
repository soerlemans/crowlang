#include "decrement.hpp"


namespace ast::node::operators {
Decrement::Decrement(NodePtr&& t_left, bool t_prefix)
  : UnaryOperator{std::move(t_left)}, m_prefix{t_prefix}
{}

auto Decrement::prefix() const -> bool
{
  return m_prefix;
}
} // namespace ast::node::operators
