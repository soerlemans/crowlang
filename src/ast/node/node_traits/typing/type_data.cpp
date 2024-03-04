#include "type_data.hpp"


namespace ast::node::node_traits::typing {
// Methods:
auto TypeData::set_type(const TypeVariant t_data) -> void
{
  m_data = t_data;
}

auto TypeData::get_type() const -> const TypeVariant&
{
  return m_data;
}
} // namespace ast::node::node_traits::typing
