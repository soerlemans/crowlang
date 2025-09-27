#include "symbol_types.hpp"

// Absolute Includes:
#include "crow/debug/log.hpp"

// Using Statements:
namespace semantic::symbol {
// StructType:
auto StructType::native_type() const -> NativeTypeOpt
{
  return {};
}

auto StructType::type_variant() const -> TypeVariant
{
  using types::core::make_struct;

  return {make_struct(m_identifier)};
}

// FnType:
auto FnType::native_type() const -> NativeTypeOpt
{
  return {};
}

auto FnType::type_variant() const -> TypeVariant
{
  using types::core::make_function;
  using types::core::TypeList;

  // TODO: Convert TypeList of @ref FnType to core::TypeList.
  TypeList params;

  return {make_function(params, m_return_type.type_variant())};
}

// VarType:
auto VarType::is_mutable() const -> bool
{
  return (m_mutability == Mutability::MUTABLE);
}

auto VarType::native_type() const -> NativeTypeOpt
{
  return m_type.native_type();
}

auto VarType::type_variant() const -> TypeVariant
{
  using types::core::make_variable;

  return {make_variable(m_type.type_variant())};
}
} // namespace semantic::symbol
