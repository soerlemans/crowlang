#ifndef CROW_CROW_CHECK_SYMBOL_TABLE_SYMBOL_TABLE_HPP
#define CROW_CROW_CHECK_SYMBOL_TABLE_SYMBOL_TABLE_HPP

// STL Include:
#include <optional>
#include <stack>
#include <string>
#include <unordered_map>

// Absolute includes:
#include "crow/check/symbol/symbol_data.hpp"

namespace check::symbol_table {
// Using Declarations:
using symbol::SymbolData;

// Forward Declarations:
struct SymbolBlock;

// Aliases:
using SymbolMapVariant = std::variant<SymbolData, SymbolBlock>;
using SymbolMap = std::unordered_map<std::string, SymbolMapVariant>;

// Structs:
/*!
 * Helper struct meant to add a nested functionality.
 * On top of the @ref SymbolData class.
 * This way we can nest the @ref SymbolTable.
 */
struct SymbolBlock {
  SymbolData m_data;
  SymbolMap m_table;
};

// Classes:
/*!
 * This classes stores the symbol table.
 */
class SymbolTable {
  private:
  SymbolMap m_table;

  public:
  SymbolTable() = default;

  // TODO: Implement.
  auto insert(SymbolMap::value_type t_pair)
    -> std::pair<SymbolMap::iterator, bool>;
  auto lookup(std::string_view t_symbol_name) -> void;

  virtual ~SymbolTable() = default;
};
} // namespace check::symbol_table

#endif // CROW_CROW_CHECK_SYMBOL_TABLE_SYMBOL_TABLE_HPP
