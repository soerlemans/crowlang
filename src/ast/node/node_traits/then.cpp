#include "then.hpp"


using namespace ast::node::node_traits;

Then::Then(NodePtr&& t_then): m_then{std::move(t_then)}
{}

auto Then::then() -> NodePtr&
{
  return m_then;
}
