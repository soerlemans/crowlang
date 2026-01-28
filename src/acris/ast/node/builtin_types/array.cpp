#include "array.hpp"

namespace ast::node::builtin_types {
// Methods:
Array::Array(TextPosition t_pos, NodePtr&& t_left, const usz t_size)
  : NodePosition{std::move(t_pos)},
    UnaryOperator{std::move(t_left)},
    m_size{t_size}
{}

auto Array::size() const -> usz
{
  return m_size;
}
} // namespace ast::node::builtin_types
