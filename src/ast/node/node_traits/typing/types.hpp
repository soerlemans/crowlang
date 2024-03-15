#ifndef CROW_AST_NODE_NODE_TRAITS_TYPING_TYPES_HPP
#define CROW_AST_NODE_NODE_TRAITS_TYPING_TYPES_HPP

// Local Includes:
#include "type_variant.hpp"

namespace ast::node::node_traits::typing {
// Structs:
// TODO: use VarTypePtr and FnTypePtr in combination with a map?
struct StructType {
  std::string m_identifier;

  auto native_type() const -> typing::NativeTypeOpt;
};

struct FnType {
  TypeList m_params;
  TypeVariant m_return_type;

  auto native_type() const -> typing::NativeTypeOpt;
};

struct VarType {
  TypeVariant m_type;

  auto native_type() const -> typing::NativeTypeOpt;
};

// Functions:
template<typename... Args>
inline auto make_struct(Args&&... t_args) -> TypeVariant
{
  return std::make_shared<StructType>(std::forward<Args>(t_args)...);
}

template<typename... Args>
inline auto make_function(Args&&... t_args) -> TypeVariant
{
  return std::make_shared<FnType>(std::forward<Args>(t_args)...);
}

template<typename... Args>
inline auto make_variable(Args&&... t_args) -> TypeVariant
{
  return std::make_shared<VarType>(std::forward<Args>(t_args)...);
}
} // namespace ast::node::node_traits::typing

#endif // CROW_AST_NODE_NODE_TRAITS_TYPING_TYPES_HPP
