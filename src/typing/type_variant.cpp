#include "type_variant.hpp"

// Includes:
#include "../debug/log.hpp"


// Using Statements:
using namespace typing;

NODE_USING_ALL_NAMESPACES()

// Private Functions:
namespace {
// TODO: Implement
// auto get_type(const StructType) -> NativeType
// {
// 	DBG_ERROR("TODO: StructType get_type is not yet implemented");

// 	throw std::runtime_error
// }

auto get_ntype(const FnTypePtr t_fn) -> NativeType
{
  NativeType type;

  if(t_fn) {
    type = t_fn->m_return_type.get_type();
  } else {
    throw std::runtime_error{"VarTypePtr is nullptr!"};
  }

  return type;
}

auto get_ntype(const VarTypePtr t_var) -> NativeType
{
  NativeType type;

  if(t_var) {
    type = t_var->m_type.get_type();
  } else {
    throw std::runtime_error{"VarTypePtr is nullptr!"};
  }

  return type;
}

auto get_ntype(const NativeType t_type) -> NativeType
{
  return t_type;
}
} // namespace

// Methods:
auto TypeVariant::get_type() const -> NativeType
{
  return std::visit(
    [](const auto& t_type) {
      return get_ntype(t_type);
    },
    *this);
}

// Functions:
// auto operator<<(std::ostream& t_os, StructType t_struct) -> std::ostream&
// {
//   DBG_ERROR("TODO: StructType is not implemented yet;\n");
//
//   return t_os;
// }

auto operator<<(std::ostream& t_os, FnTypePtr t_fn) -> std::ostream&
{
  if(t_fn) {
    t_os << "Params: ";
    for(const auto& param : t_fn->m_params) {
      t_os << param << ",";
    }
    t_os << "\n";

    t_os << "Return type: " << t_fn->m_return_type << "\n";
  } else {
    DBG_ERROR("FnTypePtr t_var is nullptr!");
  }

  return t_os;
}

auto operator<<(std::ostream& t_os, VarTypePtr t_var) -> std::ostream&
{
  if(t_var) {
    if(t_var->m_const) {
      t_os << "Const ";
    }

    t_os << t_var->m_type << "\n";
  } else {
    DBG_ERROR("VarTypePtr t_var is nullptr!");
  }

  return t_os;
}

auto operator<<(std::ostream& t_os, const TypeVariant t_variant)
  -> std::ostream&
{
  std::visit(
    [&](const auto& t_v) {
      t_os << t_v;
    },
    t_variant);

  return t_os;
}
