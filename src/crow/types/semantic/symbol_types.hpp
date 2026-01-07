#ifndef CROW_CROW_TYPES_SEMANTIC_SYMBOL_TYPES_HPP
#define CROW_CROW_TYPES_SEMANTIC_SYMBOL_TYPES_HPP

// STL Includes:
#include <map>
#include <set>
#include <string>

// Local Includes:
#include "symbol_data.hpp"

/*!
 * @file
 *
 * TODO: Describe @ref TypeVariant usage and why it is a good idea.
 */

namespace semantic::symbol {
// Forward Declarations;
class SymbolData;

// Aliases:
using MemberMap = std::map<std::string, SymbolData>;
using MethodMap = std::map<std::string, SymbolData>;
using IdentifierSet = std ::set<std::string>;

using MemberSymbol = MethodMap::value_type;
using MethodSymbol = MethodMap::value_type;

// Enums:
enum class Mutability {
  IMMUTABLE,
  MUTABLE
};

// Structs:
struct EnumType {
  SymbolData m_underlying_type;
  IdentifierSet m_enums;
};

// TODO: use VarTypePtr and FnTypePtr in combination with a map?
// This way we will be able to couple id's to type info.
/*!
 */
struct StructType {
  std::string m_identifier;

  MemberMap m_members;
  MethodMap m_methods;

  // We dont need a resolve_result_type() function cause a struct.
  // Is already a result type.

  auto native_type() const -> NativeTypeOpt;
  auto type_variant() const -> TypeVariant;

  auto operator==(const StructType&) const -> bool = default;
};

// TODO: Add utilities for verifying if parameters and their types line up.
struct FnType {
  SymbolDataList m_params;
  SymbolData m_return_type;

  auto resolve_result_type() const -> SymbolData;

  auto native_type() const -> NativeTypeOpt;
  auto type_variant() const -> TypeVariant;

  auto operator==(const FnType&) const -> bool = default;
};

struct PointerType {
  SymbolData m_type;

  auto resolve_result_type() const -> SymbolData;

  auto native_type() const -> NativeTypeOpt;
  auto type_variant() const -> TypeVariant;

  auto operator==(const PointerType&) const -> bool = default;
};

// TODO: Ignore m_const value when comparing
struct VarType {
  Mutability m_mutability;
  SymbolData m_type;

  auto is_mutable() const -> bool;
  auto resolve_result_type() const -> SymbolData;

  auto native_type() const -> NativeTypeOpt;
  auto type_variant() const -> TypeVariant;

  auto operator==(const VarType&) const -> bool = default;
};

// Functions:
template<typename... Args>
auto make_struct(Args&&... t_args) -> SymbolData
{
  return std::make_shared<StructType>(std::forward<Args>(t_args)...);
}

template<typename... Args>
auto make_function(Args&&... t_args) -> SymbolData
{
  return {std::make_shared<FnType>(std::forward<Args>(t_args)...)};
}

template<typename... Args>
auto make_variable(Args&&... t_args) -> SymbolData
{
  return {std::make_shared<VarType>(std::forward<Args>(t_args)...)};
}
} // namespace semantic::symbol

#endif // CROW_CROW_TYPES_SEMANTIC_SYMBOL_TYPES_HPP
