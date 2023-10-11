#ifndef CROW_TYPING_TYPE_VARIANT_HPP
#define CROW_TYPING_TYPE_VARIANT_HPP

// Includes:
#include "../ast/visitor/node_visitor.hpp"

// Local Includes:
#include "native_types.hpp"


namespace typing {
// Using statements:
using namespace ast;
using visitable::Any;

// Forward Declarations:
struct StructType;
struct FnType;
struct VarType;

class TypeVariant;

// Aliases:
using StructTypePtr = std::shared_ptr<VarType>;
using FnTypePtr = std ::shared_ptr<FnType>;
using VarTypePtr = std::shared_ptr<VarType>;

using TypeList = std::vector<TypeVariant>;

using Variant = std::variant<FnTypePtr, VarTypePtr, NativeType>;


// Classes:
//! This is an abbreviation for TypeVariant
class TypeVariant : public Variant {
  private:
  public:
  // Forward all constructors to base class
  using Variant::Variant;

  auto get_type() const -> NativeType;

  // auto operator==(StructTypePtr t_ptr) -> bool;
  auto operator==(FnTypePtr t_ptr) -> bool;
  auto operator==(VarTypePtr t_ptr) -> bool;
  auto operator==(NativeType t_ptr) -> bool;
  auto operator==(TypeVariant t_variant) -> bool;

  virtual ~TypeVariant() = default;
};

// Structs:
// TODO: use VarTypePtr and FnTypePtr in combination with a map?
struct StructType {
  std::string m_identifier;

	// TODO: Add members and methods
};

struct FnType {
  TypeList m_params;
  TypeVariant m_return_type;
};

struct VarType {
  bool m_const;
  TypeVariant m_type;
};
} // namespace typing

// Functions:
auto operator<<(std::ostream& t_os, typing::StructTypePtr t_struct)
  -> std::ostream&;
auto operator<<(std::ostream& t_os, typing::FnTypePtr t_fn) -> std::ostream&;
auto operator<<(std::ostream& t_os, typing::VarTypePtr t_var) -> std::ostream&;
auto operator<<(std::ostream& t_os, typing::TypeVariant t_variant)
  -> std::ostream&;

#endif // CROW_TYPING_TYPE_VARIANT_HPP
