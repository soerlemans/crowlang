#include "unary_operator.hpp"


namespace ast::node::node_traits {
// Methods:
UnaryOperator::UnaryOperator(NodePtr&& t_left): m_left{std::move(t_left)}
{}

auto UnaryOperator::left() -> NodePtr&
{
  return m_left;
}
} // namespace ast::node::node_traits
