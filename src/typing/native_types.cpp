#include "native_types.hpp"


namespace {
// Using Statements:
using namespace typing;

//! Check if a NativeType is one of the following arguments
template<typename... Args>
constexpr auto nt_any_of(const NativeType& t_nt, Args&&... t_args) -> bool
{
  return ((t_nt == t_args) || ...);
}
} // namespace

namespace typing {
// Functions:
auto is_integer(const NativeType t_nt) -> bool
{
  // clang-format off
  return nt_any_of(t_nt,
									 // Signed integers:
									 NativeType::INT,
									 NativeType::I8, NativeType::I16,
                   NativeType::I32, NativeType::I64,
									 NativeType::I128,

									 // Unsigned integers:
									 NativeType::UINT,
									 NativeType::U8, NativeType::U16,
									 NativeType::U32, NativeType::U64,
									 NativeType::U128);

  // clang-format on
}

auto is_float(const NativeType t_nt) -> bool
{
  return nt_any_of(t_nt, NativeType::F32, NativeType::F64);
}

auto is_bool(const NativeType t_typev) -> bool
{
  return t_typev == NativeType::BOOL;
}

//! Checks if a given type is a legal paramter for a condition
auto is_condition(const NativeType t_typev) -> bool
{
  if(is_bool(t_typev) || is_integer(t_typev)) {
    return true;
  } else {
    return false;
  }
}

auto is_numeric(const NativeType t_typev) -> bool
{
  return is_integer(t_typev) || is_float(t_typev);
}

auto nativetype2str(const NativeType t_ntype) -> std::string
{
  std::string id;
  auto& rmap{native_types.right};

  const auto iter{rmap.find(t_ntype)};
  if(iter != rmap.end()) {
    id = iter->second;
  }

  return id;
}
} // namespace typing

auto operator<<(std::ostream& t_os, const typing::NativeType t_type)
  -> std::ostream&
{
  t_os << typing::nativetype2str(t_type);

  return t_os;
}
