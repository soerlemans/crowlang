#include "binary_operator.hpp"


using namespace ast::node::node_traits;

BinaryOperator::BinaryOperator(NodePtr&& t_left, NodePtr&& t_right)
  : UnaryOperator{std::move(t_left)}, m_right{std::move(t_right)}
{}

auto BinaryOperator::right() -> NodePtr&
{
  return m_right;
}
