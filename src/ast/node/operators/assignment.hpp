#ifndef CROW_AST_NODE_OPERATORS_ASSIGNMENT_HPP
#define CROW_AST_NODE_OPERATORS_ASSIGNMENT_HPP

#include "binary_operator.hpp"
#include "operators.hpp"


enum AssignmentOp {
  POWER = 0,

  MULTIPLY,
  DIVIDE,
  MODULO,

  ADD,
  SUBTRACT,

  REGULAR
};

namespace node::operators {
class Assignment : public BinaryOperator {
  private:
  AssignmentOp m_op;

  public:
  Assignment(AssignmentOp t_op, NodePtr&& t_left, NodePtr&& t_right);

  auto op() const -> AssignmentOp;

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~Assignment() override = default;
};
} // namespace node::operators

#endif // CROW_AST_NODE_OPERATORS_ASSIGNMENT_HPP
