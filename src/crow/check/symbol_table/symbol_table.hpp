#ifndef SYMBOL_TABLE_HPP
#define SYMBOL_TABLE_HPP

// STL Include:
#include <optional>
#include <stack>
#include <string>
#include <unordered_map>

// Absolute includes:
#include "crow/check/symbol/symbol.hpp"

namespace check::symbol_table {
// Using Declarations:
using symbol::SymbolData;

// Aliases:
using SymbolMap = std::unordered_map<std::string, SymbolData>;

// Clases:
/*!
 * This class gives
 */
class SymbolTable {
  private:
  SymbolMap m_table;

  public:
  SymbolTable() = default;

  // TODO: Implement.
  auto insert(SymbolMap::value_type t_pair) -> bool;
  auto lookup(std::string t_symbol_name) -> void;

  virtual ~SymbolTable() = default;
};
} // namespace check::symbol_table

#endif // SYMBOL_TABLE_HPP
