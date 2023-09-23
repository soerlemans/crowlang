#include "assignment.hpp"


using namespace ast::node::operators;
using namespace ast::node::node_traits;

Assignment::Assignment(AssignmentOp t_op, NodePtr&& t_left, NodePtr&& t_right)
  : BinaryOperator{std::move(t_left), std::move(t_right)}, m_op{t_op}
{}

auto Assignment::op() const -> AssignmentOp
{
  return m_op;
}
