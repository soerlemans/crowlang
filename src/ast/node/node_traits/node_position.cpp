#include "node_position.hpp"

namespace ast::node::node_traits {
// Methods:
NodePosition::NodePosition(TextPosition&& t_pos): m_pos{std::move(t_pos)}
{}

auto NodePosition::position() -> const TextPosition&
{
  return m_pos;
}
} // namespace ast::node::node_traits
