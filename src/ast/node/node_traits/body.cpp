#include "body.hpp"


using namespace ast::node::node_traits;

Body::Body(NodeListPtr&& t_body): m_body{std::move(t_body)}
{}

auto Body::body() -> NodeListPtr&
{
  return m_body;
}
