#ifndef CROW_CHECK_SYMBOL_DATA_HPP
#define CROW_CHECK_SYMBOL_DATA_HPP

// Local Includes:
#include "../ast/node/node_traits/typing/native_types.hpp"
#include "symbol_types.hpp"


namespace check {
// Using Statements:
using namespace ast::node::node_traits;

// Aliases:
using Variant =
  std::variant<StructTypePtr, FnTypePtr, VarTypePtr, typing::NativeType>;

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
  auto native_type() const -> typing::NativeTypeOpt;

  virtual ~SymbolData() = default;
};

// Structs:
// TODO: use VarTypePtr and FnTypePtr in combination with a map?
struct StructType {
  std::string m_identifier;

  auto native_type() const -> typing::NativeTypeOpt
  {
    return {};
  }
};

struct FnType {
  TypeList m_params;
  SymbolData m_return_type;

  auto native_type() const -> typing::NativeTypeOpt
  {
    return {};
  }
};

// TODO: Ignore m_const value when comparing
struct VarType {
  bool m_const;
  SymbolData m_type;

  auto native_type() const -> typing::NativeTypeOpt
  {
    return m_type.native_type();
  }
};
} // namespace check

// Functions:
auto operator<<(std::ostream& t_os, const check::SymbolData& t_data)
  -> std::ostream&;

#endif // CROW_CHECK_SYMBOL_DATA_HPP
