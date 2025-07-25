#include "symbol_tree.hpp"


// STL Includes:
#include <iomanip>
#include <string_view>

// Absolute Includes:
#include "lib/iomanip/iomanip.hpp"
#include "lib/stdprint.hpp"

namespace symbol_table {
SymbolTree::SymbolTree(): m_tree{}
{}

auto SymbolTree::insert(const SymbolMapEntry t_pair) -> SymbolTreeResult
{
  const auto [iter, inserted] = m_tree.insert(t_pair);
  if(!inserted) {
    return std::unexpected{SymbolTreeError::INSERT_FAILED};
  }

  return {iter};
}

auto SymbolTree::insert(SymbolMapIter t_parent, const SymbolMapEntry t_pair)
  -> SymbolTreeResult
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
    return std::unexpected{SymbolTreeError::INSERT_FAILED};
  }

  return {iter};
}

auto SymbolTree::lookup(const std::string_view t_symbol_name) const
  -> SymbolTreeResult
{
  // TODO: Implement.

  return std::unexpected{SymbolTreeError::UNIMPLEMENTED};
}

auto SymbolTree::lookup_toplevel(const std::string_view t_symbol_name) const
  -> SymbolTreeResult
{
  // TODO: Implement.

  return std::unexpected{SymbolTreeError::UNIMPLEMENTED};
}

auto SymbolTree::tree() const -> const SymbolMap&
{
  return m_tree;
}

auto SymbolTree::begin() -> SymbolMapIter
{
  return m_tree.begin();
}

auto SymbolTree::end() -> SymbolMapIter
{
  return m_tree.end();
}

auto SymbolTree::clear() -> void
{
  m_tree.clear();
}
} // namespace symbol_table

// Functions:
auto operator<<(std::ostream& t_os,
                const symbol_table::SymbolTreeScope& t_scope) -> std::ostream&
{
  const auto& [symbol_id, scope_opt] = t_scope;

  // Print symbol id.
  t_os << '"' << symbol_id << '"';

  // Only show scope if it exists.
  if(scope_opt) {
    t_os << ", scope: {";
    t_os << scope_opt.value();
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
    const auto& [symbol_name, scope] = elem;

    t_os << sep << cond_nl;
    t_os << std::quoted(symbol_name) << ": " << scope;

    sep = ", ";
  }
  t_os << cond_nl;

  return t_os;
}

auto operator<<(std::ostream& t_os,
                const symbol_table::SymbolTree& t_symbol_tree) -> std::ostream&
{
  const auto& tree{t_symbol_tree.tree()};
  t_os << "SymbolTree{" << tree << '}';

  return t_os;
}

auto operator<<(std::ostream& t_os, const symbol_table::SymbolTreePtr& t_ptr)
  -> std::ostream&
{
  using lib::stdprint::detail::print_smart_ptr;

  return print_smart_ptr(t_os, t_ptr);
}
