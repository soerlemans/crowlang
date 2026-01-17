#include "type_annotation.hpp"

namespace ast::node::node_traits {
// Methods:
TypeAnnotation::TypeAnnotation(NodePtr&& t_type): m_type{t_type}
{}

auto TypeAnnotation::type() const -> NodePtr
{
  return m_type;
}
} // namespace ast::node::node_traits
