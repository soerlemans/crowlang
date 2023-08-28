#include "assignment.hpp"


using namespace node::operators;

using namespace visitor;

Assignment::Assignment(AssignmentOp t_op, NodePtr&& t_left, NodePtr&& t_right)
  : BinaryOperator{std::forward<NodePtr>(t_left),
                   std::forward<NodePtr>(t_right)},
    m_op{t_op}
{}

auto Assignment::op() const -> AssignmentOp
{
  return m_op;
}
