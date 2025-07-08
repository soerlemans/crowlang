#ifndef CROW_CROW_TYPES_SEMANTIC_SYMBOL_TYPES_HPP
#define CROW_CROW_TYPES_SEMANTIC_SYMBOL_TYPES_HPP

// Local Includes:
#include "symbol_data.hpp"

/*!
 * @file
 *
 * TODO: Describe TypeVariant usage and why it is a good idea.
 */

namespace semantic::symbol {
// Structs:
// TODO: use VarTypePtr and FnTypePtr in combination with a map?
// This way we will be able to couple id's to type info.
struct StructType {
  std::string m_identifier;

  auto native_type() const -> NativeTypeOpt;
  auto type_variant() const -> TypeVariant;
};

// TODO: Add utilities for verifying if parameters and their types line up.
struct FnType {
  SymbolDataList m_params;
  SymbolData m_return_type;

  auto native_type() const -> NativeTypeOpt;
  auto type_variant() const -> TypeVariant;
};

// TODO: Ignore m_const value when comparing
struct VarType {
  bool m_const;
  SymbolData m_type;

  auto native_type() const -> NativeTypeOpt;
  auto type_variant() const -> TypeVariant;
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
