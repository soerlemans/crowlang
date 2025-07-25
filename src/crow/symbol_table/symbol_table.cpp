#include "symbol_table.hpp"

// STL Includes:
#include <iomanip>
#include <string_view>

// Absolute Includes:
#include "lib/iomanip/iomanip.hpp"
#include "lib/stdprint.hpp"

// Functions:
auto operator<<(std::ostream& t_os,
                const symbol_table::SymbolTable& t_symbol_table)
  -> std::ostream&
{
  const auto& table{t_symbol_table.table()};
  t_os << "SymbolTable{" << table << '}';

  return t_os;
}

auto operator<<(std::ostream& t_os, const symbol_table::SymbolTablePtr& t_ptr)
  -> std::ostream&
{
  using lib::stdprint::detail::print_smart_ptr;

  return print_smart_ptr(t_os, t_ptr);
}
