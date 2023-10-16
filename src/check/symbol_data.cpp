#include "symbol_data.hpp"

// Includes:
#include "../debug/log.hpp"


// Using Statements:
using namespace check;

//! Structs can not be resolved to Native types
auto SymbolData::native_type([[maybe_unused]] const StructTypePtr t_struct)
  const -> NativeTypeOpt
{
  NativeTypeOpt opt;

  return opt;
}

auto SymbolData::native_type(const FnTypePtr t_fn) const -> NativeTypeOpt
{
  NativeTypeOpt opt;

  if(t_fn) {
    opt = t_fn->m_return_type.native_type();
  } else {
    throw std::runtime_error{"VarTypePtr is nullptr!"};
  }

  return opt;
}

auto SymbolData::native_type(const VarTypePtr t_var) const -> NativeTypeOpt
{
  NativeTypeOpt opt;

  if(t_var) {
    opt = t_var->m_type.native_type();
  } else {
    throw std::runtime_error{"VarTypePtr is nullptr!"};
  }

  return opt;
}

auto SymbolData::native_type(const NativeType t_type) const -> NativeTypeOpt
{
  return t_type;
}

// Methods:
auto SymbolData::native_type() const -> NativeTypeOpt
{
  NativeTypeOpt opt;

  std::visit(
    [&](const auto& t_data) {
      opt = native_type(t_data);
    },
    *this);

  return opt;
}

// Functions:
auto operator<<(std::ostream& t_os, const SymbolData t_variant) -> std::ostream&
{
  std::visit(
    [&](const auto& t_v) {
      t_os << t_v;
    },
    t_variant);

  return t_os;
}
