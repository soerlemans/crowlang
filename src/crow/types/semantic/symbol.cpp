#include "symbol.hpp"

// STL Includes:
#include <iostream>

// Absolute Includes:
#include "crow/debug/log.hpp"

// Local Includes:
#include "symbol_types.hpp"


// Using Statements:
using namespace semantic::symbol;
using namespace std::literals::string_view_literals;

// Functions:
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

auto operator<<(std::ostream& t_os, VarTypePtr t_var) -> std::ostream&
{
  if(t_var) {
    if(t_var->is_mutable()) {
      t_os << "mutable ";
    }

    t_os << t_var->m_type;
  } else {
    DBG_ERROR("(VarTypePtr) nullptr!");

    t_os << "nullptr";
  }

  return t_os;
}

auto operator<<(std::ostream& t_os, const SymbolDataList& t_list)
  -> std::ostream&
{
  using namespace std::literals::string_view_literals;

  auto sep{""sv};
  for(const auto& elem : t_list) {
    t_os << sep << elem;
    sep = ", ";
  }

  return t_os;
}
