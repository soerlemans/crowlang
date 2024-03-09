#include "alt.hpp"

namespace ast::node::node_traits {
// Methods:
Alt::Alt(NodePtr&& t_alt): m_alt{std::move(t_alt)}
{}

auto Alt::alt() -> NodePtr&
{
  return m_alt;
}
} // namespace ast::node::node_traits
