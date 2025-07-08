#ifndef CROW_CROW_TYPES_SEMANTIC_SYMBOL_DATA_HPP
#define CROW_CROW_TYPES_SEMANTIC_SYMBOL_DATA_HPP

// Absolute Includes:
#include "crow/types/core/core_types.hpp"

// Local Includes:
#include "symbol.hpp"

/*!
 * @file
 *
 * TODO: Describe the differences between the @ref TypeVariant.
 * And @ref SymbolData.
 */

namespace semantic::symbol {
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
 * As this also constitues data relating to a symbol.
 * Like constness and other helper methods.
 * @ref TypeVariant has a separate type tree.
 * And you need to convert between these two.
 */
class SymbolData : public Variant {
  public:
  // Use the constructors of the parent class.
  using Variant::Variant;

  // Only use these methods if you are sure about the underlying type.
  auto struct_() const -> StructTypePtr;
  auto function() const -> FnTypePtr;
  auto var() const -> VarTypePtr;

  //! Verify if a symbol is immutable.
  auto is_const() const -> bool;

  /*!
   * Stripts non type related information from the @ref SymbolData.
   * Variables are resolved to their underlying types.
   */
  auto resolve_type() const -> SymbolData;

  /*!
   * Resolves a Symbol's data  to a @ref NativeType if possible.
   * Usefull for when dealing with native type only operations.
   * Like type promotion in arithmetic/comparison operations.
   */
  auto native_type() const -> NativeTypeOpt;

  /*!
   * Used to convert @ref SymbolData to a  @ref typing::TypeVariant.
   * The type tree for @ref SymbolData contains extra information.
   * Like if a symbol is const or pure.
   * When we annotate the AST we dont want to include this information.
   * So this information is stripped.
   */
  auto type_variant() const -> TypeVariant;

  virtual ~SymbolData() = default;
};
} // namespace semantic::symbol

// Functions:
auto operator<<(std::ostream& t_os, const semantic::symbol::SymbolData& t_data)
  -> std::ostream&;

#endif // CROW_CROW_TYPES_SEMANTIC_SYMBOL_DATA_HPP
