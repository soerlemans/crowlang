#include "comparison.hpp"

namespace ast::node::operators {
Comparison::Comparison(TextPosition t_pos, ComparisonOp t_op, NodePtr&& t_left,
                       NodePtr&& t_right)
  : NodePosition{std::move(t_pos)},
    Op{t_op},
    BinaryOperator{std::move(t_left), std::move(t_right)}
{}
} // namespace ast::node::operators
