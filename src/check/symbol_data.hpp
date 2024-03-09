#ifndef CROW_CHECK_SYMBOL_DATA_HPP
#define CROW_CHECK_SYMBOL_DATA_HPP

// Includes:
#include "../ast/node/node_traits/typing/types.hpp"

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

  auto strip() const -> TypeVariant;

  virtual ~SymbolData() = default;
};
} // namespace check

// Functions:
auto operator<<(std::ostream& t_os, const check::SymbolData& t_data)
  -> std::ostream&;

#endif // CROW_CHECK_SYMBOL_DATA_HPP
