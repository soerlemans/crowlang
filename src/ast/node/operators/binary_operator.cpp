#include "binary_operator.hpp"

using namespace node::operators;

using namespace visitor;


BinaryOperator::BinaryOperator(NodePtr&& t_lhs, NodePtr&& t_rhs)
  : UnaryOperator{std::forward<NodePtr>(t_lhs)},
    m_right{std::forward<NodePtr>(t_rhs)}
{}

auto BinaryOperator::right() -> NodePtr&
{
  return m_right;
}
