#include "binary_operator.hpp"


using namespace ast::node::node_traits;

BinaryOperator::BinaryOperator(NodePtr&& t_lhs, NodePtr&& t_rhs)
  : UnaryOperator{std::move(t_lhs)}, m_right{std::move(t_rhs)}
{}

auto BinaryOperator::right() -> NodePtr&
{
  return m_right;
}
