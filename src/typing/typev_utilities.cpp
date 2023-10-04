#include "typev_utilities.hpp"

// Includes:
#include "../ast/node/include.hpp"
#include "../debug/log.hpp"

// Using Statements:
using namespace typing;

NODE_USING_ALL_NAMESPACES()

// Methods:
auto TypeVVisitor::get_typev(NodePtr t_ptr) -> TypeV
{
  TypeV typev;

  auto any{traverse(t_ptr)};
  if(any.has_value()) {
    try {
      typev = std::any_cast<TypeV>(any);
    } catch(const std::bad_any_cast& e) {
      DBG_CRITICAL(e.what());
    }
  }

  return typev;
}

// Functions:
namespace typing {
auto is_integer(const TypeV& t_typev) -> bool
{
  // clang-format off
  return typev_any_of(t_typev,
									 NativeType::INT,
									 NativeType::I8, NativeType::I16,
                   NativeType::I32, NativeType::I64,
									 NativeType::I128,

									 // Unsigned
									 NativeType::UINT,
									 NativeType::U8, NativeType::U16,
									 NativeType::U32, NativeType::U64,
									 NativeType::U128);

  // clang-format on
}

auto is_float(const TypeV& t_typev) -> bool
{
  return typev_any_of(t_typev, NativeType::F32, NativeType::F64);
}

auto is_bool(const TypeV& t_typev) -> bool
{
  return t_typev == TypeV{NativeType::BOOL};
}

//! Checks if a given type is a legal paramter for a condition
auto is_condition(const TypeV& t_typev) -> bool
{
  if(is_bool(t_typev) || is_integer(t_typev)) {
    return true;
  } else {
    return false;
  }
}

auto is_numeric(const TypeV& t_typev) -> bool
{
  return is_integer(t_typev) || is_float(t_typev);
}
} // namespace typing

auto operator<<(std::ostream& t_os, const TypeV t_typev) -> std::ostream&
{
  std::visit(
    [&](const auto& t_v) {
      t_os << t_v;
    },
    t_typev);

  return t_os;
}
