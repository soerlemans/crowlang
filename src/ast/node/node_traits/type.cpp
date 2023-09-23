#include "type.hpp"


using namespace ast::node::node_traits;

Type::Type(const std::string_view t_type): m_type{t_type}
{}

auto Type::type() const -> std::string_view
{
  return m_type;
}
