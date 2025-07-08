#include "core_types.hpp"

// Absolute Includes:
#include "crow/debug/log.hpp"

// Using Statements:
namespace types::core {
// StructType:
auto StructType::native_type() const -> core::NativeTypeOpt
{
  return {};
}

// FnType:
auto FnType::native_type() const -> core::NativeTypeOpt
{
  return {};
}

// VarType:
auto VarType::native_type() const -> core::NativeTypeOpt
{
  return m_type.native_type();
}

} // namespace types::core

// Functions:
auto operator<<(std::ostream& t_os, types::core::StructTypePtr t_struct)
  -> std::ostream&
{
  if(t_struct) {
    t_os << "Identifier: " << t_struct->m_identifier;
  } else {
    DBG_ERROR("(StructTypePtr) nullptr!");

    t_os << "nullptr";
  }

  return t_os;
}

auto operator<<(std::ostream& t_os, types::core::FnTypePtr t_fn) -> std::ostream&
{
  using namespace std::literals::string_view_literals;

  if(t_fn) {
    auto sep{""sv};
    t_os << "(";
    for(const auto& param : t_fn->m_params) {
      t_os << sep << param;

      sep = ", ";
    }
    t_os << ") -> " << t_fn->m_return_type;

  } else {
    DBG_ERROR("(FnTypePtr) nullptr!");

    t_os << "nullptr";
  }

  return t_os;
}

auto operator<<(std::ostream& t_os, types::core::VarTypePtr t_var) -> std::ostream&
{
  if(t_var) {
    t_os << t_var->m_type;
  } else {
    DBG_ERROR("(VarTypePtr) nullptr!");

    t_os << "nullptr";
  }

  return t_os;
}

auto operator<<(std::ostream& t_os, const types::core::TypeList& t_list) -> std::ostream&
{
  std::string_view sep{""};
  for(const auto& elem : t_list) {
    t_os << sep << elem;

    sep = ", ";
  }

  return t_os;
}
