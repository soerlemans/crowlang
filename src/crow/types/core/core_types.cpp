#include "core_types.hpp"

// Absolute Includes:
#include "crow/debug/log.hpp"

// Using Statements:
namespace types::core {
// StructType:
auto StructType::native_type() const -> core::NativeTypeOpt
{
  return {};
}

// FnType:
auto FnType::native_type() const -> core::NativeTypeOpt
{
  return {};
}

// VarType:
auto VarType::native_type() const -> core::NativeTypeOpt
{
  return m_type.native_type();
}

} // namespace types::core
