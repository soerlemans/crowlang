#include "symbol_data.hpp"

// STL Includes:
#include <format>
#include <functional>

// Absolute Includes:
#include "crow/debug/log.hpp"
#include "crow/exception/error.hpp"
#include "lib/overload.hpp"

// Local Includes:
#include "symbol_types.hpp"

// Internal:
namespace {
/*!
 * Check if a @ref std::shared_ptr is a nullptr or not.
 * If the given ptr is a nullptr we should throw.
 * Only use in cases where you are certain a nullptr should never happen.
 */
template<typename T>
auto nullptr_check(const std::string_view t_str,
                   const std::shared_ptr<T>& t_ptr) -> void
{
  using exception::error;

  if(!t_ptr) {
    const auto msg{std::format("{} ptr is nullptr!", t_str)};

    error("ptr is nullptr!");
  }
}
} // namespace

namespace semantic::symbol {
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
    nullptr_check("Variable", t_data);

    return t_data->m_const;
  }};

  const auto not_const{[]([[maybe_unused]]
                          const auto& t_data) {
    return false;
  }};

  result = std::visit(Overload{var_type, not_const}, *this);

  return result;
}

auto SymbolData::resolve_type() const -> SymbolData
{
  SymbolData data;

  // If we can resolve to a native type then return that.
  // Else just return the instance itself.
  if(const auto opt{native_type()}; opt) {
    data = opt.value();
  } else {
    data = *this;
  }

  return data;
}

auto SymbolData::native_type() const -> NativeTypeOpt
{
  NativeTypeOpt opt;

  const auto native{[&](const NativeType t_type) -> NativeTypeOpt {
    return t_type;
  }};

  const auto rest{[&](const std::shared_ptr<auto>& t_data) {
    nullptr_check("Non native", t_data);

    return t_data->native_type();
  }};

  opt = std::visit(Overload{native, rest}, *this);

  return opt;
}

auto SymbolData::type_variant() const -> TypeVariant
{
  TypeVariant variant;

  const auto native{[&](const NativeType t_type) -> TypeVariant {
    return {t_type};
  }};

  // Calls variant() method of types defined in symbol_types.hpp header.
  const auto rest{[&](const std::shared_ptr<auto>& t_data) {
    nullptr_check("Non native", t_data);

    return t_data->type_variant();
  }};

  variant = std::visit(Overload{native, rest}, *this);

  return variant;
}
} // namespace semantic::symbol

// Functions:
auto operator<<(std::ostream& t_os, const semantic::symbol::SymbolData& t_data)
  -> std::ostream&
{
  std::visit(
    [&](auto&& t_v) {
      t_os << t_v;
    },
    t_data);

  return t_os;
}
