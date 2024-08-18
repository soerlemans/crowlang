#ifndef CROW_CROW_AST_NODE_NODE_TRAITS_TYPING_TYPE_VARIANT_HPP
#define CROW_CROW_AST_NODE_NODE_TRAITS_TYPING_TYPE_VARIANT_HPP

// STL Includes:
#include <variant>

// Local Includes:
#include "native_types.hpp"
#include "typing.hpp"

namespace ast::node::node_traits::typing {
// Using Statements:
using ast::node::node_traits::typing::NativeType;

// Aliases:
using Variant = std::variant<StructTypePtr, FnTypePtr, VarTypePtr, NativeType>;

// Classes:
// FIXME: We probably should probably not inherit from Variant.
// Instead we should prefer composition.
/*!
 * Recursive @ref Variant tree structure that denotes the type tree of a symbol.
 * This class unlike @ref SymbolData solely holds the type information.
 * The type tree is also a separate one from @ref SymbolData.
 */
class TypeVariant : public Variant {
  public:
  // Use the constructors of the parent class.
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
