#include "pointer.hpp"

namespace ast::node::user_types {
// Methods:
Pointer::Pointer(TextPosition t_pos, NodePtr&& t_left)
  : NodePosition{std::move(t_pos)}, UnaryOperator{std::move(t_left)}
{}
} // namespace ast::node::user_types
