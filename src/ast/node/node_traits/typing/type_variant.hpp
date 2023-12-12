#ifndef CROW_AST_NODE_NODE_TRAITS_TYPE_DATA_TYPE_VARIANT_HPP
#define CROW_AST_NODE_NODE_TRAITS_TYPE_DATA_TYPE_VARIANT_HPP

// STL Includes:
#include <variant>

// Local Includes:
#include "native_types.hpp"
#include "types.hpp"


namespace ast::node::node_traits::typing {
// Aliases:
using Variant =
  std::variant<StructTypePtr, FnTypePtr, VarTypePtr, typing::NativeType>;

// Classes:
/*!
 * Contains all data relating to a symbol.
 */
class TypeVariant : public Variant {
  public:
  // Use the constructors of the variant
  using Variant::Variant;

  auto struct_() const -> StructTypePtr;
  auto function() const -> FnTypePtr;
  auto var() const -> VarTypePtr;

  auto native_type() const -> typing::NativeTypeOpt;

  virtual ~TypeVariant() = default;
};

// Structs:
// TODO: use VarTypePtr and FnTypePtr in combination with a map?
struct StructType {
  std::string m_identifier;

  auto native_type() const -> typing::NativeTypeOpt
  {
    return {};
  }
};

struct FnType {
  TypeList m_params;
  TypeVariant m_return_type;

  auto native_type() const -> typing::NativeTypeOpt
  {
    return {};
  }
};

struct VarType {
  TypeVariant m_type;

  auto native_type() const -> typing::NativeTypeOpt
  {
    return m_type.native_type();
  }
};

// Functions:
// auto operator<<(std::ostream& t_os, const typing::TypeVariant& t_data)
// -> std::ostream&;
} // namespace ast::node::node_traits::type_data

#endif // CROW_AST_NODE_NODE_TRAITS_TYPE_DATA_TYPE_VARIANT_HPP
