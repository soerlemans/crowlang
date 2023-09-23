#include "arithmetic.hpp"


using namespace ast::node::operators;
using namespace ast::node::node_traits;

Arithmetic::Arithmetic(ArithmeticOp t_op, NodePtr&& t_left, NodePtr&& t_right)
  : BinaryOperator{std::move(t_left), std::move(t_right)}, m_op{t_op}
{}

auto Arithmetic::op() -> ArithmeticOp
{
  return m_op;
}
