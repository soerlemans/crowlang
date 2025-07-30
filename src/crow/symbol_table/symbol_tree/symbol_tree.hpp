#ifndef CROW_CROW_SYMBOL_TABLE_SYMBOL_TREE_SYMBOL_TREE_HPP
#define CROW_CROW_SYMBOL_TABLE_SYMBOL_TREE_SYMBOL_TREE_HPP

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

// TODO: Define a immutable interface for querying the symbol tree.

namespace symbol_table::symbol_tree {
// Forward Declarations:
enum class SymbolTreeError;
struct SymbolTreeScope;
class SymbolTree;

// Aliases:
using SymbolMap = std::map<std::string, SymbolTreeScope>;
using SymbolMapOpt = std::optional<SymbolMap>;
using SymbolMapEntry = SymbolMap::value_type;
using SymbolMapIter = SymbolMap::iterator;

// TODO: Consider making this a struct, with a possible enum tag for the type.
// That the symbol entails, (roughly if its a function, struct, variable,
// global, etc).
using SymbolTreeId = u64;

using SymbolTreeResult = std::expected<SymbolMapIter, SymbolTreeError>;
using SymbolTreePtr = std::shared_ptr<SymbolTree>;

// enums:
enum class SymbolTreeError {
  INSERT_FAILED,

  PARENT_ITER_HAS_NO_SCOPE,

  SYMBOL_NOT_FOUND,
  SYMBOL_NOT_FOUND_TOPLEVEL,
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
  //! Symbol ID, resolvable to concrete symbol related metadatadata.
  //! Stored in a @ref SymbolRegister.
  SymbolTreeId m_id;

  SymbolMapOpt m_scope; //!< Optional nested scope containing more symbols.
};

// Classes:
/*!
 * This classes stores the global symbol table.
 * This keeps track of all the symbols in a module.
 */
class SymbolTree {
  private:
  SymbolMap m_tree;
  std::size_t m_count;

  // TODO: In order to optimize performance.
  // Define an unordered_multimap, which contains iterators to each symbol.
  // This way we can perform lookups across the board performantly.
  // Without needing to recursively find.

  public:
  SymbolTree();

  // TODO: Implement.
  auto insert(SymbolMapIter t_parent, SymbolMapEntry t_pair)
    -> SymbolTreeResult;
  auto insert_toplevel(SymbolMapEntry t_pair) -> SymbolTreeResult;

  // TODO: Make new std::expected type so we can make these const methods.
  auto lookup(SymbolMapIter t_parent, std::string_view t_symbol_name)
    -> SymbolTreeResult;
  auto lookup_toplevel(std::string_view t_symbol_name) -> SymbolTreeResult;

  auto tree() const -> const SymbolMap&;

  auto begin() -> SymbolMapIter;
  auto end() -> SymbolMapIter;

  auto size() const -> std::size_t;
  auto clear() -> void;

  virtual ~SymbolTree() = default;
};
} // namespace symbol_table::symbol_tree

// Functions:
auto symbol_tree_error2str(symbol_table::symbol_tree::SymbolTreeError t_error)
  -> std::string_view;

auto operator<<(std::ostream& t_os,
                const symbol_table::symbol_tree::SymbolTreeError& t_error)
  -> std::ostream&;
auto operator<<(std::ostream& t_os,
                const symbol_table::symbol_tree::SymbolTreeScope& t_scope)
  -> std::ostream&;
auto operator<<(std::ostream& t_os,
                const symbol_table::symbol_tree::SymbolMap& t_map)
  -> std::ostream&;
auto operator<<(std::ostream& t_os,
                const symbol_table::symbol_tree::SymbolTree& t_symbol_table)
  -> std::ostream&;
auto operator<<(std::ostream& t_os,
                const symbol_table::symbol_tree::SymbolTreePtr& t_ptr)
  -> std::ostream&;


#endif // CROW_CROW_SYMBOL_TABLE_SYMBOL_TREE_SYMBOL_TREE_HPP
