#include "unary_operator.hpp"

using namespace node::operators;

using namespace visitor;


UnaryOperator::UnaryOperator(NodePtr&& t_left)
  : m_left{std::forward<NodePtr>(t_left)}
{}

auto UnaryOperator::left() -> NodePtr&
{
  return m_left;
}
