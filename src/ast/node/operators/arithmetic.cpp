#include "arithmetic.hpp"


using namespace node::operators;

using namespace visitor;

Arithmetic::Arithmetic(ArithmeticOp t_op, NodePtr&& t_left, NodePtr&& t_right)
  // TODO: Fix the selection of the precedence
  : BinaryOperator{std::forward<NodePtr>(t_left),
                   std::forward<NodePtr>(t_right)},
    m_op{t_op}
{}

auto Arithmetic::op() -> ArithmeticOp
{
  return m_op;
}
