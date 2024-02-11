#include "assignment.hpp"


namespace ast::node::operators {
Assignment::Assignment(TextPosition t_pos, const AssignmentOp t_op,
                       NodePtr&& t_left, NodePtr&& t_right)
  : NodePosition{std::move(t_pos)},
    Op{t_op},
    BinaryOperator{std::move(t_left), std::move(t_right)}
{}
} // namespace ast::node::operators
