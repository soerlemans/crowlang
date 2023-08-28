#include "unary_operator.hpp"


using namespace ast::node::operators;

UnaryOperator::UnaryOperator(NodePtr&& t_left): m_left{std::move(t_left)}
{}

auto UnaryOperator::left() -> NodePtr&
{
  return m_left;
}
