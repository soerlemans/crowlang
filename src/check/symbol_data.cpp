#include "symbol_data.hpp"

// Includes:
#include "../debug/log.hpp"
#include "../overload.hpp"
#include "native_types.hpp"
#include "symbol_types.hpp"


// Using Statements:
using namespace check;

//! Structs can not be resolved to Native types
auto SymbolData::native_type(
  [[maybe_unused]] const StructTypePtr t_struct) const -> NativeTypeOpt
{
  return {};
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

// Methods:
auto SymbolData::struct_() -> StructTypePtr
{
  return std::get<StructTypePtr>(*this);
}

auto SymbolData::function() -> FnTypePtr
{
  return std::get<FnTypePtr>(*this);
}

auto SymbolData::var() -> VarTypePtr
{
  return std::get<VarTypePtr>(*this);
}

auto SymbolData::is_const() const -> bool
{
  bool result{false};

  const auto var_type{[&](const VarTypePtr& t_data) {
    if(t_data) {
      return t_data->m_const;
    }

    return false;
  }};

  const auto not_const{[]([[maybe_unused]] const auto& t_data) {
    return false;
  }};

  result = std::visit(Overload{var_type, not_const}, *this);

  return result;
}

//! All data except information related to types is stripped
auto SymbolData::resolve_type() const -> SymbolData
{
  SymbolData data;

  if(auto opt{native_type()}; opt) {
    data = opt.value();
  } else {
    data = *this;
  }

  return data;
}

//! Resolves a Symbol's data  to a NativeType if possible
auto SymbolData::native_type() const -> NativeTypeOpt
{
  NativeTypeOpt opt;

  const auto native{[&](const NativeType t_type) -> NativeTypeOpt {
    return t_type;
  }};

  const auto methods{[&](const auto& t_data) {
    return native_type(t_data);
  }};

  opt = std::visit(Overload{native, methods}, *this);

  return opt;
}

// Functions:
auto operator<<(std::ostream& t_os, const SymbolData& t_data) -> std::ostream&
{
  std::visit(
    [&](const auto& t_v) {
      t_os << t_v;
    },
    t_data);

  return t_os;
}
