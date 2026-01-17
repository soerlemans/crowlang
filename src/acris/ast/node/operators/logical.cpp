#include "logical.hpp"

namespace ast::node::operators {
// Not:
Not::Not(TextPosition t_pos, NodePtr&& t_left)
  : NodePosition{std::move(t_pos)}, UnaryOperator{std::move(t_left)}
{}

// And:
And::And(TextPosition t_pos, NodePtr&& t_left, NodePtr&& t_right)
  : NodePosition{std::move(t_pos)},
    BinaryOperator{std::move(t_left), std::move(t_right)}
{}

// Or:
Or::Or(TextPosition t_pos, NodePtr&& t_left, NodePtr&& t_right)
  : NodePosition{std::move(t_pos)},
    BinaryOperator{std::move(t_left), std::move(t_right)}
{}
} // namespace ast::node::operators
