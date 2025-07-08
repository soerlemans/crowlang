#include "core_types.hpp"

// Absolute Includes:
#include "crow/debug/log.hpp"

// Using Statements:
namespace ast::node::node_traits::typing {
// StructType:
auto StructType::native_type() const -> typing::NativeTypeOpt
{
  return {};
}

// FnType:
auto FnType::native_type() const -> typing::NativeTypeOpt
{
  return {};
}

// VarType:
auto VarType::native_type() const -> typing::NativeTypeOpt
{
  return m_type.native_type();
}

} // namespace ast::node::node_traits::typing
