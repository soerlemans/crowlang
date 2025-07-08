#include "native_types.hpp"

// STL Includes:
#include <stdexcept>

// Includes:
#include "crow/debug/log.hpp"

// Using Statements:
using types::core::NativeType;
using types::core::NativeTypeOpt;

namespace {
// TODO: Move to somewhere in src/lib and make it more generic.
//! Check if a @ref NativeType is one of the following arguments.
template<typename... Args>
constexpr auto any_of(const NativeType& t_key, Args&&... t_args) -> bool
{
  return ((t_key == t_args) || ...);
}
} // namespace

namespace types::core {
// Functions:
auto is_integer(const NativeType t_native_type) -> bool
{
  // clang-format off
  return any_of(t_native_type,
		// Signed integers:
		NativeType::INT,
		NativeType::I8, NativeType::I16,
		NativeType::I32, NativeType::I64,
		NativeType::ISIZE,

		// Unsigned integers:
		NativeType::UINT,
		NativeType::U8, NativeType::U16,
		NativeType::U32, NativeType::U64,
		NativeType::USIZE);

  // clang-format on
}

auto is_float(const NativeType t_native_type) -> bool
{
  return any_of(t_native_type, NativeType::F32, NativeType::F64);
}

auto is_bool(const NativeType t_native_type) -> bool
{
  return t_native_type == NativeType::BOOL;
}

/*!
 * Checks if a certain @ref NativeType can be used in a condition.
 * Only booleans and integers may be used for conditionals.
 */
auto is_condition(const NativeType t_native_type) -> bool
{
  if(is_bool(t_native_type) || is_integer(t_native_type)) {
    return true;
  } else {
    return false;
  }
}

auto is_numeric(const NativeType t_native_type) -> bool
{
  return is_integer(t_native_type) || is_float(t_native_type);
}

auto str2nativetype(const std::string_view t_str) -> NativeType
{
  NativeType type;
  auto& lmap{native_types.left};

  const std::string str{t_str};

  // We need to compare using a std::string
  const auto iter{lmap.find(str)};
  if(iter != lmap.end()) {
    type = iter->second;
  } else {
    DBG_ERROR("Cant convert ", std::quoted(t_str), " to NativeType!");

    throw std::invalid_argument{"String could not be converted to NativeType."};
  }

  return type;
}

auto nativetype2str(const NativeType t_native_type) -> std::string
{
  std::string id;
  auto& rmap{native_types.right};

  const auto iter{rmap.find(t_native_type)};
  if(iter != rmap.end()) {
    id = iter->second;
  } else {
    std::string_view str{"NativeType could not be converted to std::string."};
    DBG_ERROR(str);

    throw std::invalid_argument{str.data()};
  }

  return id;
}
} // namespace types::core

auto operator<<(std::ostream& t_os, const NativeType t_native_type)
  -> std::ostream&
{
  t_os << nativetype2str(t_native_type);

  return t_os;
}

auto operator<<(std::ostream& t_os, const NativeTypeOpt& t_opt) -> std::ostream&
{
  if(t_opt) {
    t_os << t_opt.value();
  } else {
    t_os << "<NativeTypeOpt empty>";
  }

  return t_os;
}
