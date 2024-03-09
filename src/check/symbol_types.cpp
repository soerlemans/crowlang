#include "symbol_types.hpp"

// Includes:
#include "../debug/log.hpp"

// Using Statements:
namespace check {
// StructType:
auto StructType::strip() const -> TypeVariant
{
  namespace typing = ast::node::node_traits::typing;

  return {typing::make_struct(m_identifier)};
}

// FnType:
auto FnType::strip() const -> TypeVariant
{
  namespace typing = ast::node::node_traits::typing;

  typing::TypeList params;

  return {typing::make_function(params, m_return_type.strip())};
}

// VarType:
auto VarType::strip() const -> TypeVariant
{
  namespace typing = ast::node::node_traits::typing;

  return {typing::make_variable(m_type.strip())};
}
} // namespace check
