#include "binding_map.hpp"

namespace parser::pratt::binding {
// Methods:
auto BindingMap::insert_binding(const TokenType t_type, const int t_lbp,
                                const int t_rbp) -> void
{
  const BindingPower pair{t_lbp, t_rbp};

  m_map.insert({t_type, pair});
}

auto BindingMap::at(const TokenType t_type) const -> BindingPower
{
  return m_map.at(t_type);
}

auto BindingMap::rbp(const TokenType t_type) const -> int
{
  return m_map.at(t_type).second;
}

auto BindingMap::lbp(const TokenType t_type) const -> int
{
  return m_map.at(t_type).first;
}
} // namespace parser::pratt::binding
