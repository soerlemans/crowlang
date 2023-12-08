#include "symbol_data.hpp"

// Includes:
#include "../debug/log.hpp"
#include "../exception/error.hpp"
#include "../lib/overload.hpp"


// Local Includes:
#include "native_types.hpp"
#include "symbol_types.hpp"


// Using Statements:
using namespace check;

// Methods:
auto SymbolData::struct_() const -> StructTypePtr
{
  return std::get<StructTypePtr>(*this);
}

auto SymbolData::function() const -> FnTypePtr
{
  return std::get<FnTypePtr>(*this);
}

auto SymbolData::var() const -> VarTypePtr
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

//! All data except information related to types is stripped.
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

//! Resolves a Symbol's data  to a NativeType if possible.
auto SymbolData::native_type() const -> NativeTypeOpt
{
  using namespace exception;

  NativeTypeOpt opt;

  const auto native{[&](const NativeType t_type) -> NativeTypeOpt {
    return t_type;
  }};

  const auto methods{[&](const std::shared_ptr<auto>& t_data) {
    if(!t_data) {
      error("ptr is nullptr!");
    }

    return t_data->native_type();
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
