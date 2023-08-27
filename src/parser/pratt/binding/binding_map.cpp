#include "binding_map.hpp"


using namespace parser::pratt::binding;

auto BindingMap::insert_binding(const token::TokenType t_type, const int t_lbp,
                                const int t_rbp) -> void
{
  this->insert({t_type, BindingPower{t_lbp, t_rbp}});
}

auto BindingMap::rbp(token::TokenType t_type) const -> int
{
  return this->at(t_type).second;
}

auto BindingMap::lbp(token::TokenType t_type) const -> int
{
  return this->at(t_type).first;
}
