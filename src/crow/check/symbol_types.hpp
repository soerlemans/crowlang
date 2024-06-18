#ifndef CROW_CROW_CHECK_SYMBOL_TYPES_HPP
#define CROW_CROW_CHECK_SYMBOL_TYPES_HPP

// Local Includes:
#include "symbol_data.hpp"

namespace check {
// Structs:
// TODO: use VarTypePtr and FnTypePtr in combination with a map?
struct StructType {
  std::string m_identifier;

  auto native_type() const -> NativeTypeOpt
  {
    return {};
  }

  auto strip() const -> TypeVariant;
};

struct FnType {
  TypeList m_params;
  SymbolData m_return_type;

  auto native_type() const -> NativeTypeOpt
  {
    return {};
  }

  auto strip() const -> TypeVariant;
};

// TODO: Ignore m_const value when comparing
struct VarType {
  bool m_const;
  SymbolData m_type;

  auto native_type() const -> NativeTypeOpt
  {
    return m_type.native_type();
  }

  auto strip() const -> TypeVariant;
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
} // namespace check

#endif // CROW_CROW_CHECK_SYMBOL_TYPES_HPP
