#include "binary_operator.hpp"

namespace ast::node::node_traits {
// Methods:
BinaryOperator::BinaryOperator(NodePtr&& t_left, NodePtr&& t_right)
  : UnaryOperator{std::move(t_left)}, m_right{std::move(t_right)}
{}

auto BinaryOperator::right() -> NodePtr&
{
  return m_right;
}
} // namespace ast::node::node_traits
