#include "body.hpp"


namespace ast::node::node_traits {
// Methods:
Body::Body(NodeListPtr&& t_body): m_body{std::move(t_body)}
{}

auto Body::body() -> NodeListPtr&
{
  return m_body;
}
} // namespace ast::node::node_traits
