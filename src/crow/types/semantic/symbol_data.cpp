#include "symbol_data.hpp"

// STL Includes:
#include <format>
#include <functional>

// Absolute Includes:
#include "crow/debug/log.hpp"
#include "lib/is_any_of.hpp"
#include "lib/overload.hpp"
#include "lib/stdexcept/stdexcept.hpp"

// Local Includes:
#include "symbol_types.hpp"

// Internal:
namespace {
// TODO: Move somewhere proper.
// Used to guarentee evaluation in else branches, to trigger static_assert().
template<typename T>
inline constexpr bool always_false = false;

/*!
 * Check if a @ref std::shared_ptr is a nullptr or not.
 * If the given ptr is a nullptr we should throw.
 * Only use in cases where you are certain a nullptr should never happen.
 */
template<typename T>
auto nullptr_check(const std::string_view t_str,
                   const std::shared_ptr<T>& t_ptr) -> void
{
  using lib::stdexcept::throw_unexpected_nullptr;

  if(!t_ptr) {
    const auto msg{std::format("{} ptr is nullptr!", t_str)};

    throw_unexpected_nullptr("ptr is nullptr!");
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
  using lib::Overload;

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
  using lib::Overload;

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
  using lib::Overload;

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

auto SymbolData::operator==(const SymbolData& t_rhs) const -> bool
{
  bool equal{false};
  const auto& lhs{*this};

  equal = std::visit(
    [](const auto& t_l, const auto& t_r) -> bool {
      using L = std::decay_t<decltype(t_l)>;
      using R = std::decay_t<decltype(t_r)>;

      // Make sure the types are the same.
      if constexpr(std::is_same_v<L, R>) {
        if constexpr(std::is_same_v<L, NativeType>) {
          // NativeType is just a simple compare.
          return t_l == t_r;
        } else if constexpr(lib::IsAnyOf<L, StructTypePtr, FnTypePtr,
                                         VarTypePtr>) {
          // Return
          if(t_l && t_r) {
            // Compare resolved pointers.
            return (*t_l == *t_r);
          } else {
            return false;
          }
        } else {
          static_assert(always_false<L>, "Unhandled type.");
        }
      }

      return false;
    },
    lhs, t_rhs);

  return equal;
}

auto SymbolData::operator!=(const SymbolData& t_rhs) const -> bool
{
  const auto& lhs{*this};

  // Use ==.
  return !(lhs == t_rhs);
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

