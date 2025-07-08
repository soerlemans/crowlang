#ifndef CROW_CROW_TYPES_CORE_TYPE_VARIANT_HPP
#define CROW_CROW_TYPES_CORE_TYPE_VARIANT_HPP

// STL Includes:
#include <variant>

// Local Includes:
#include "fdecl.hpp"
#include "native_types.hpp"

namespace types::core {
// Using Statements:
using types::core::NativeType;

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

  auto native_type() const -> core::NativeTypeOpt;

  virtual ~TypeVariant() = default;
};
} // namespace types::core

// Functions:
auto operator<<(std::ostream& t_os, const types::core::TypeVariant& t_data)
  -> std::ostream&;

#endif // CROW_CROW_TYPES_CORE_TYPE_VARIANT_HPP
