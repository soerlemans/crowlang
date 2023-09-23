#include "alt.hpp"

using namespace ast::node::node_traits;

Alt::Alt(NodePtr&& t_alt): m_alt{std::move(t_alt)}
{}

auto Alt::alt() -> NodePtr&
{
  return m_alt;
}


