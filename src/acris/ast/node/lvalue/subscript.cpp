#include "subscript.hpp"

namespace ast::node::lvalue {
// Methods:
Subscript::Subscript(TextPosition t_pos, NodePtr&& t_expr, NodePtr&& t_index)
  : NodePosition{std::move(t_pos)},
    BinaryOperator{std::move(t_expr), std::move(t_index)}
{}
} // namespace ast::node::lvalue
