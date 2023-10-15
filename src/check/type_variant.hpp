#ifndef CROW_CHECK_TYPE_VARIANT_HPP
#define CROW_CHECK_TYPE_VARIANT_HPP

// Includes:
#include "../ast/visitor/node_visitor.hpp"

// Local Includes:
#include "native_types.hpp"


namespace check {
// Using statements:
using namespace ast;
using visitable::Any;

// Forward Declarations:
class TypeVariant;

struct StructType;
struct FnType;
struct VarType;

// Aliases:
using StructTypePtr = std::shared_ptr<StructType>;
using FnTypePtr = std ::shared_ptr<FnType>;
using VarTypePtr = std::shared_ptr<VarType>;

using TypeList = std::vector<TypeVariant>;

using Variant = std::variant<FnTypePtr, VarTypePtr, NativeType>;


// Classes:
//! This is an abbreviation for TypeVariant
class TypeVariant : public Variant {
  public:
  // Forward all constructors to base class
  using Variant::Variant;

  auto get_type() const -> NativeType;

  virtual ~TypeVariant() = default;
};

// Structs:
// TODO: use VarTypePtr and FnTypePtr in combination with a map?
struct StructType {
  std::string m_identifier;
};

struct FnType {
  TypeList m_params;
  TypeVariant m_return_type;
};

struct VarType {
  bool m_const;
  TypeVariant m_type;
};
} // namespace check

// Functions:
auto operator<<(std::ostream& t_os, check::StructTypePtr t_struct)
  -> std::ostream&;
auto operator<<(std::ostream& t_os, check::FnTypePtr t_fn) -> std::ostream&;
auto operator<<(std::ostream& t_os, check::VarTypePtr t_var) -> std::ostream&;
auto operator<<(std::ostream& t_os, check::TypeVariant t_variant)
  -> std::ostream&;

#endif // CROW_CHECK_TYPE_VARIANT_HPP
