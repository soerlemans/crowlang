#include "symbol_table.hpp"

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
