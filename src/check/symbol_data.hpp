#ifndef CROW_CHECK_SYMBOL_DATA_HPP
#define CROW_CHECK_SYMBOL_DATA_HPP

// Local Includes:
#include "symbol_types.hpp"


namespace check {
// Aliases:
using Variant = std::variant<StructTypePtr, FnTypePtr, VarTypePtr, NativeType>;

// Classes:
//! This is an abbreviation for SymbolData
class SymbolData : public Variant {
  protected:
  auto native_type(StructTypePtr t_struct) const -> NativeTypeOpt;
  auto native_type(FnTypePtr t_fn) const -> NativeTypeOpt;
  auto native_type(VarTypePtr t_var) const -> NativeTypeOpt;

  public:
  // Use the constructors of the base class
  using Variant::Variant;

  auto struct_() -> StructTypePtr;
  auto function() -> FnTypePtr;
  auto var() -> VarTypePtr;

  auto is_const() const -> bool;
  auto native_type() const -> NativeTypeOpt;

  virtual ~SymbolData() = default;
};

// Structs:
// TODO: use VarTypePtr and FnTypePtr in combination with a map?
struct StructType {
  std::string m_identifier;
};

struct FnType {
  TypeList m_params;
  SymbolData m_return_type;
};

// TODO: Ignore m_const value when comparing
struct VarType {
  bool m_const;
  SymbolData m_type;
};

} // namespace check

// Functions:
auto operator<<(std::ostream& t_os, const check::SymbolData& t_data) -> std::ostream&;

#endif // CROW_CHECK_SYMBOL_DATA_HPP
