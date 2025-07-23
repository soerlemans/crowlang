#include "symbol_table.hpp"

// STL Includes:
#include <iomanip>
#include <string_view>

// Absolute Includes:
#include "lib/stdprint.hpp"

namespace symbol_table {
SymbolTable::SymbolTable(): m_table{}
{}

auto SymbolTable::insert(const SymbolMapEntry t_pair) -> SymbolTableResult
{
  const auto [iter, inserted] = m_table.insert(t_pair);
  if(!inserted) {
    return std::unexpected{SymbolTableError::INSERT_FAILED};
  }

  return {iter};
}

auto SymbolTable::insert(SymbolMapIter t_parent, const SymbolMapEntry t_pair)
  -> SymbolTableResult
{
  // Get a reference to the scope of the parent.
  auto& scope_ref{t_parent->second};
  auto& opt{scope_ref.m_scope};

  // If this is the first element, initialize the scope.
  if(!opt) {
    opt.emplace();
  }

  auto& map{opt.value()};
  const auto [iter, inserted] = map.insert(t_pair);
  if(!inserted) {
    return std::unexpected{SymbolTableError::INSERT_FAILED};
  }

  return {iter};
}

auto SymbolTable::lookup(const std::string_view t_symbol_name) const
  -> SymbolTableResult
{
  // TODO: Implement.

  return std::unexpected{SymbolTableError::UNIMPLEMENTED};
}

auto SymbolTable::lookup_toplevel(const std::string_view t_symbol_name) const
  -> SymbolTableResult
{
  // TODO: Implement.

  return std::unexpected{SymbolTableError::UNIMPLEMENTED};
}

auto SymbolTable::table() const -> const SymbolMap&
{
  return m_table;
}

auto SymbolTable::begin() -> SymbolMapIter
{
  return m_table.begin();
}

auto SymbolTable::end() -> SymbolMapIter
{
  return m_table.end();
}

auto SymbolTable::clear() -> void
{
  m_table.clear();
}
} // namespace symbol_table

// Functions:
auto operator<<(std::ostream& t_os,
                const symbol_table::SymbolTableScope& t_scope) -> std::ostream&
{
  const auto& [data, opt] = t_scope;

  // Add
  t_os << '"' << data << '"';

  // Only show scope if it exists.
  if(opt) {
    t_os << ", scope: {";
    t_os << opt.value();
    t_os << '}';
  }

  return t_os;
}

auto operator<<(std::ostream& t_os, const symbol_table::SymbolMap& t_map)
  -> std::ostream&
{
  using namespace std::literals::string_view_literals;
  using lib::iomanip::cond_nl;

  auto sep{""sv};
  for(const auto& elem : t_map) {
    const auto& [id, scope] = elem;

    t_os << sep << cond_nl;
    t_os << std::quoted(id) << ": " << scope;
    sep = ", ";
  }

  return t_os;
}

auto operator<<(std::ostream& t_os,
                const symbol_table::SymbolTable& t_symbol_table)
  -> std::ostream&
{
  using lib::iomanip::cond_nl;

  const auto table{t_symbol_table.table()};

  t_os << '{' << table;
  t_os << cond_nl << '}';

  return t_os;
}

auto operator<<(std::ostream& t_os, const symbol_table::SymbolTablePtr& t_ptr)
  -> std::ostream&
{
  using lib::stdprint::detail::print_smart_ptr;

  return print_smart_ptr(t_os, t_ptr);
}
