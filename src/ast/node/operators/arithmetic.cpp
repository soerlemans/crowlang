#include "arithmetic.hpp"


namespace ast::node::operators {
// Methods:
Arithmetic::Arithmetic(TextPosition t_pos, const ArithmeticOp t_op,
                       NodePtr&& t_left, NodePtr&& t_right)
  : NodePosition{std::move(t_pos)},
    Op{t_op},
    BinaryOperator{std::move(t_left), std::move(t_right)}
{}
} // namespace ast::node::operators
