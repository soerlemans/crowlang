#ifndef CROW_CROW_CHECK_SYMBOL_DATA_HPP
#define CROW_CROW_CHECK_SYMBOL_DATA_HPP

// Absolute Includes:
#include "crow/ast/node/node_traits/typing/types.hpp"

// Local Includes:
#include "check.hpp"

namespace check {
// Using Statements:
using ast::node::node_traits::typing::NativeType;
using ast::node::node_traits::typing::NativeTypeOpt;
using ast::node::node_traits::typing::TypeVariant;

// Aliases:
using Variant = std::variant<StructTypePtr, FnTypePtr, VarTypePtr, NativeType>;

// Classes:
// FIXME: We probably should probably not inherit from Variant.
// Instead we should prefer composition.
/*!
 * Contains all data relating to a symbol.
 * This is different from @ref TypeVariant.
 * As this also constitues data ralting to a symbol.
 * Like constness and other helper methods.
 * @ref TypeVariant has a separate type tree.
 * And you need to convert between these two.
 */
class SymbolData : public Variant {
  public:
  // Use the constructors of the parent class.
  using Variant::Variant;

  auto struct_() const -> StructTypePtr;
  auto function() const -> FnTypePtr;
  auto var() const -> VarTypePtr;

  auto is_const() const -> bool;
  auto resolve_type() const -> SymbolData;
  auto native_type() const -> NativeTypeOpt;

  /*!
   * Used to convert @ref SymbolData to a  @ref typing::TypeVariant.
   * The type tree for @ref SymbolData is different..
   * From @ref TypeVariant and requires conversion.
   * When we annotate the AST we dont want to include symbol specifics.
   * Like if something is const or pure.
   * So this information is stripped.
   */
  auto type_variant() const -> TypeVariant;

  virtual ~SymbolData() = default;
};
} // namespace check

// Functions:
auto operator<<(std::ostream& t_os, const check::SymbolData& t_data)
  -> std::ostream&;

#endif // CROW_CROW_CHECK_SYMBOL_DATA_HPP
