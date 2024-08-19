#include "symbol_types.hpp"

// Absolute Includes:
#include "crow/debug/log.hpp"

// Using Statements:
namespace check {
// StructType:
auto StructType::type_variant() const -> TypeVariant
{
  using ast::node::node_traits::typing::make_struct;

  return {make_struct(m_identifier)};
}

// FnType:
auto FnType::type_variant() const -> TypeVariant
{
  using ast::node::node_traits::typing::make_function;
  using ast::node::node_traits::typing::TypeList;

  // TODO: Convert TypeList of @ref FnType to typing::TypeList.
  TypeList params;

  return {make_function(params, m_return_type.type_variant())};
}

// VarType:
auto VarType::type_variant() const -> TypeVariant
{
  using ast::node::node_traits::typing::make_variable;

  return {make_variable(m_type.type_variant())};
}
} // namespace check
