#include "node_position.hpp"


using namespace container;
using namespace ast::node::node_traits;

NodePosition::NodePosition(TextPosition&& t_pos): m_pos{std::move(t_pos)}
{}

auto NodePosition::position() -> const TextPosition&
{
  return m_pos;
}
