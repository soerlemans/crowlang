#include "symbol_table.hpp"

// STL Includes:
#include <iomanip>
#include <string_view>

namespace check::symbol_table {
SymbolTable::SymbolTable(): m_table{}
{}

auto SymbolTable::insert(const SymbolEntry t_pair)
  -> std::pair<SymbolMap::iterator, bool>
{
  return m_table.insert(t_pair);
}

auto SymbolTable::lookup(const std::string_view t_symbol_name) const
  -> SymbolData
{
  // TODO: Implement.
}

auto SymbolTable::lookup_toplevel(const std::string_view t_symbol_name) const
  -> SymbolData
{
  // TODO: Implement.
}

auto SymbolTable::table() const -> const SymbolMap&
{
  return m_table;
}

auto SymbolTable::clear() -> void
{
  m_table.clear();
}
} // namespace check::symbol_table

// Functions:
auto operator<<(std::ostream& t_os,
                const check::symbol_table::SymbolBlock& t_block)
  -> std::ostream&
{
  const auto& [data, table] = t_block;

  t_os << '{' << data;
  if(table)
    t_os << ", " << table.value();
  t_os << '}';

  return t_os;
}

auto operator<<(std::ostream& t_os, const check::symbol_table::SymbolMap& t_map)
  -> std::ostream&
{
  using namespace std::literals::string_view_literals;

  auto sep{""sv};
  for(const auto& elem : t_map) {
    const auto& [id, block] = elem;

    t_os << sep << std::quoted(id) << ':' << block;
    sep = ", ";
  }

  return t_os;
}

auto operator<<(std::ostream& t_os,
                const check::symbol_table::SymbolTable& t_symbol_table)
  -> std::ostream&
{
  const auto table{t_symbol_table.table()};

  t_os << '{' << table << '}';

  return t_os;
}
