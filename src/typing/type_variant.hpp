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

using TypeVec = std::vector<TypeVariant>;

using Variant = std::variant<FnTypePtr, VarTypePtr, NativeType>;


// Classes:
//! This is an abbreviation for TypeVariant
class TypeVariant : public Variant {
  private:
  public:
	// Forward all constructors to base class
  using Variant::Variant;

  auto get_type() const -> NativeType;

  virtual ~TypeVariant() = default;
};

// Structs:
// TODO: use VarTypePtr and FnTypePtr in combination with a map?
struct StructType {};

struct FnType {
  TypeVec m_params;
  TypeVariant m_return_type;
};

struct VarType {
  bool m_const;
  TypeVariant m_type;
};
} // namespace typing

// auto operator<<(std::ostream& t_os, typing::StructTypePtr t_struct)
//   -> std::ostream&;

auto operator<<(std::ostream& t_os, typing::FnTypePtr t_fn) -> std::ostream&;

auto operator<<(std::ostream& t_os, typing::VarTypePtr t_var) -> std::ostream&;

auto operator<<(std::ostream& t_os, typing::TypeVariant t_variant)
  -> std::ostream&;

#endif // CROW_TYPING_TYPE_VARIANT_HPP
