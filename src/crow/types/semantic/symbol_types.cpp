#include "symbol_types.hpp"

// Absolute Includes:
#include "crow/debug/log.hpp"

// Using Statements:
namespace types::symbol {
// StructType:
auto StructType::native_type() const -> NativeTypeOpt
{
  return {};
}

auto StructType::type_variant() const -> TypeVariant
{
  using types::core::make_struct;

  types::core::MemberMap member_map{};
  for(auto& [id, data] : m_members) {
    member_map.emplace(id, data.type_variant());
  }

  types::core::MemberMap method_map{};
  for(auto& [id, data] : m_methods) {
    method_map.emplace(id, data.type_variant());
  }

  return {make_struct(m_identifier, member_map, method_map)};
}

// FnType:
auto FnType::resolve_result_type() const -> SymbolData
{
  // Get return type as it is the result of a function call.
  return SymbolData{m_return_type};
}

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

// PointerType:
auto PointerType::resolve_result_type() const -> SymbolData
{
  // Get underlying type.
  return SymbolData{m_type};
}

auto PointerType::native_type() const -> NativeTypeOpt
{
  return m_type.native_type();
}

auto PointerType::type_variant() const -> TypeVariant
{
  using types::core::make_pointer;

  return {make_pointer(m_type.type_variant())};
}

// VarType:
auto VarType::is_mutable() const -> bool
{
  return (m_mutability == Mutability::MUTABLE);
}

auto VarType::resolve_result_type() const -> SymbolData
{
  // Get underlying type.
  return SymbolData{m_type};
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
} // namespace types::semantic::symbol
