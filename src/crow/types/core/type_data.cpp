#include "type_data.hpp"

namespace types::core {
// Methods:
auto TypeData::set_type(const TypeVariant t_data) -> void
{
  m_data = t_data;
}

auto TypeData::get_type() const -> const TypeVariant&
{
  return m_data;
}
} // namespace types::core
