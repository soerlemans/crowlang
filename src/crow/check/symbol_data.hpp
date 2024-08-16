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
/*!
 * Contains all data relating to a symbol.
 */
class SymbolData : public Variant {
  public:
  // Use the constructors of the variant
  using Variant::Variant;

  auto struct_() const -> StructTypePtr;
  auto function() const -> FnTypePtr;
  auto var() const -> VarTypePtr;

  auto is_const() const -> bool;
  auto resolve_type() const -> SymbolData;
  auto native_type() const -> NativeTypeOpt;

  /*!
   * Strip recursively resolves types to @ref NativeType's.
   * Used for getting the return type of a function as well.
   * This method is used when we are interested in the result of something.
   */
  auto strip() const -> TypeVariant;

  /*!
   * Used to return the @ref TypeVariant as is.
   * This is needed when storing type information for Functions.
   * As we dont want to strip away the types of parameters.
   */
  auto variant() const -> TypeVariant;

  virtual ~SymbolData() = default;
};
} // namespace check

// Functions:
auto operator<<(std::ostream& t_os, const check::SymbolData& t_data)
  -> std::ostream&;

#endif // CROW_CROW_CHECK_SYMBOL_DATA_HPP
