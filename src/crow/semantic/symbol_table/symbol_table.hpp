#ifndef CROW_CROW_CHECK_SYMBOL_TABLE_SYMBOL_TABLE_HPP
#define CROW_CROW_CHECK_SYMBOL_TABLE_SYMBOL_TABLE_HPP

// STL Include:
#include <map>
#include <optional>
#include <stack>
#include <string>

// Absolute includes:
#include "crow/check/symbol/symbol_data.hpp"

namespace semantic::symbol_table {
// Using Declarations:
using symbol::SymbolData;

// Forward Declarations:
struct SymbolTableScope;

// Aliases:
using SymbolMap = std::map<std::string, SymbolTableScope>;
using SymbolMapOpt = std::optional<SymbolMap>;
using SymbolMapEntry = SymbolMap::value_type;
using SymbolMapIter = SymbolMap::iterator;
using SymbolMapInsertResult = std::pair<SymbolMap::iterator, bool>;

// Structs:
/*!
 * Helper struct to add nested scope functionality.
 * On top of the @ref SymbolData class.
 * This way we can nest the @ref SymbolTable.
 * Without needing to change @ref SymbolData.
 * This way functions can optionaly
 */
struct SymbolTableScope {
  SymbolData m_data;
  SymbolMapOpt m_scope;
};

// Classes:
/*!
 * This classes stores the global symbol table.
 * This keeps track of all the symbols in a module.
 */
class SymbolTable {
  private:
  SymbolMap m_table;

  public:
  SymbolTable();

  // TODO: Implement.
  auto insert(SymbolMapEntry t_pair) -> SymbolMapInsertResult;
  auto insert(SymbolMapIter t_parent, SymbolMapEntry t_pair)
    -> SymbolMapInsertResult;

  // auto lookup(std::string_view t_symbol_name) const -> SymbolData;
  // auto lookup_toplevel(std::string_view t_symbol_name) const -> SymbolData;
  auto table() const -> const SymbolMap&;

  auto clear() -> void;

  virtual ~SymbolTable() = default;
};
} // namespace semantic::symbol_table

// Functions:
auto operator<<(std::ostream& t_os,
                const semantic::symbol_table::SymbolTableScope& t_scope)
  -> std::ostream&;
auto operator<<(std::ostream& t_os,
                const semantic::symbol_table::SymbolMap& t_map)
  -> std::ostream&;
auto operator<<(std::ostream& t_os,
                const semantic::symbol_table::SymbolTable& t_symbol_table)
  -> std::ostream&;

#endif // CROW_CROW_CHECK_SYMBOL_TABLE_SYMBOL_TABLE_HPP
