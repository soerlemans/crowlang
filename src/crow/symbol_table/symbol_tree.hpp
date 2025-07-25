#ifndef CROW_CROW_SYMBOL_TABLE_SYMBOL_TREE_HPP
#define CROW_CROW_SYMBOL_TABLE_SYMBOL_TREE_HPP

/*!
 * @file symbol_table.hpp
 *
 * In order to deal with a symbol that needs to looked up across.
 * Multiple compiler passes.
 */

// STL Include:
#include <expected>
#include <map>
#include <memory>
#include <optional>
#include <stack>
#include <string>

// Absolute includes:
#include "lib/stdtypes.hpp"

namespace symbol_table {
// Forward Declarations:
enum class SymbolTreeError;
struct SymbolTreeScope;
class SymbolTree;

// Aliases:
using SymbolMap = std::map<std::string, SymbolTreeScope>;
using SymbolMapOpt = std::optional<SymbolMap>;
using SymbolMapEntry = SymbolMap::value_type;
using SymbolMapIter = SymbolMap::iterator;

using SymbolTreeId = u64;
using SymbolTreeResult = std::expected<SymbolMapIter, SymbolTreeError>;
using SymbolTreePtr = std::shared_ptr<SymbolTree>;

// enums:
enum class SymbolTreeError {
  UNIMPLEMENTED, // FIXME: Temporary.
  INSERT_FAILED,
  SYMBOL_NOT_FOUND,
};

// Structs:
/*!
 * Helper struct to add nested scope functionality.
 * The @ref SymbolTreeId gives back an id which is an index.
 * In a register
 * This way we can nest the @ref SymbolTree.
 * Without needing to change @ref SymbolData.
 * This way functions can optionaly
 */
struct SymbolTreeScope {
  SymbolTreeId m_id;
  SymbolMapOpt m_scope;
};

// Classes:
/*!
 * This classes stores the global symbol table.
 * This keeps track of all the symbols in a module.
 */
class SymbolTree {
  private:
  SymbolMap m_tree;

  public:
  SymbolTree();

  // TODO: Implement.
  auto insert(SymbolMapEntry t_pair) -> SymbolTreeResult;
  auto insert(SymbolMapIter t_parent, SymbolMapEntry t_pair)
    -> SymbolTreeResult;

  auto lookup(std::string_view t_symbol_name) const -> SymbolTreeResult;
  auto lookup_toplevel(std::string_view t_symbol_name) const
    -> SymbolTreeResult;

  auto tree() const -> const SymbolMap&;

  auto begin() -> SymbolMapIter;
  auto end() -> SymbolMapIter;

  auto clear() -> void;

  virtual ~SymbolTree() = default;
};
} // namespace symbol_table

// Functions:
auto operator<<(std::ostream& t_os,
                const symbol_table::SymbolTreeScope& t_scope) -> std::ostream&;
auto operator<<(std::ostream& t_os, const symbol_table::SymbolMap& t_map)
  -> std::ostream&;
auto operator<<(std::ostream& t_os,
                const symbol_table::SymbolTree& t_symbol_table)
  -> std::ostream&;
auto operator<<(std::ostream& t_os, const symbol_table::SymbolTreePtr& t_ptr)
  -> std::ostream&;


#endif // CROW_CROW_SYMBOL_TABLE_SYMBOL_TREE_HPP
