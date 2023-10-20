#include "assignment.hpp"


using namespace container;
using namespace ast::node::operators;
using namespace ast::node::node_traits;

Assignment::Assignment(TextPosition t_pos, const AssignmentOp t_op,
                       NodePtr&& t_left, NodePtr&& t_right)
  : NodePosition{std::move(t_pos)},
    Op{t_op},
    BinaryOperator{std::move(t_left), std::move(t_right)}
{}
