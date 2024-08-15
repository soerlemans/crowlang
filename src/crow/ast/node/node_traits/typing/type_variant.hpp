#ifndef CROW_CROW_AST_NODE_NODE_TRAITS_TYPING_TYPE_VARIANT_HPP
#define CROW_CROW_AST_NODE_NODE_TRAITS_TYPING_TYPE_VARIANT_HPP

// STL Includes:
#include <variant>

// Local Includes:
#include "native_types.hpp"
#include "typing.hpp"

namespace ast::node::node_traits::typing {
// Aliases:
using Variant =
  std::variant<StructTypePtr, FnTypePtr, VarTypePtr, typing::NativeType>;

// Classes:
// FIXME: We probably should probably not inherit from Variant.
// Instead we should prefer composition.
/*!
 * Recursive @ref Variant tree structure that denotes the type tree of a symbol.
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
} // namespace ast::node::node_traits::typing

// Functions:
auto operator<<(std::ostream& t_os,
                const ast::node::node_traits::typing::TypeVariant& t_data)
  -> std::ostream&;

#endif // CROW_CROW_AST_NODE_NODE_TRAITS_TYPING_TYPE_VARIANT_HPP
