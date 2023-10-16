#include "symbol_types.hpp"

// Includes:
#include "../debug/log.hpp"

// Local Includes:
#include "symbol_data.hpp"


using namespace check;

// Functions:
auto operator<<(std::ostream& t_os, NativeTypeOpt t_opt) -> std::ostream&
{
  if(t_opt) {
    t_os << t_opt.value();
  } else {
    t_os << "<empty>";
  }

  return t_os;
}

auto operator<<(std::ostream& t_os, StructTypePtr t_struct) -> std::ostream&
{
  if(t_struct) {
    t_os << "Identifier: " << t_struct->m_identifier;
  } else {
    DBG_ERROR("(StructTypePtr) nullptr!");

    t_os << "nullptr";
  }

  return t_os;
}

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
    DBG_ERROR("(FnTypePtr) nullptr!");

    t_os << "nullptr";
  }

  return t_os;
}

auto operator<<(std::ostream& t_os, VarTypePtr t_var) -> std::ostream&
{
  if(t_var) {
    if(t_var->m_const) {
      t_os << "Const ";
    }

    t_os << t_var->m_type;
  } else {
    DBG_ERROR("(VarTypePtr) nullptr!");

    t_os << "nullptr";
  }

  return t_os;
}
