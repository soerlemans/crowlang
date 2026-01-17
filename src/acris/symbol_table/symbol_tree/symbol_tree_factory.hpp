#ifndef ACRIS_ACRIS_SYMBOL_TABLE_SYMBOL_TREE_SYMBOL_TREE_FACTORY_HPP
#define ACRIS_ACRIS_SYMBOL_TABLE_SYMBOL_TREE_SYMBOL_TREE_FACTORY_HPP

// STL Includes:
#include <memory>
#include <stack>

// Local includes:
#include "symbol_tree.hpp"

/*!
 * @file
 *
 * We do not use @ref std::unordered_map as insertion can trigger a rehash.
 * Rehashing invalidates iterators.
 * Which breaks the @ref SymbolMapStack which keeps track of the construction.
 * Using iterators, until this issue is addressed/fixed use @ref std::map.
 * For @ref SymbolTree.
 *
 * Alternatively we could use @ref std::unorederd_map.
 * And instead use indirect references by using a @ref std::stack<std::string>.
 * Which keeps track of the current ID nesting.
 */

namespace symbol_table::symbol_tree {
// Forward Declarations:
enum class SymbolTreeFactoryError;

// Aliases:
using SymbolTreeFactoryResult =
  std::expected<SymbolTreeId, SymbolTreeFactoryError>;


/*!
 * Used to construct the nested structure of the @ref SymbolTree.
 * Very similar to @ref EnvState.
 * But the goal is to not depend on @ref EnvState.
 * As @ref EnvState is intended for multipurpose quick lookups.
 * During AST traversal, and shadowing variables is not allowed.
 * A better construction should be possible, reconsider soon.
 */
using SymbolMapStack = std::stack<SymbolMap::iterator>;

// Enums:
enum class SymbolTreeFactoryError {
};

// Classes:
/*!
 */
class SymbolTreeFactory {
  private:
  SymbolTreePtr m_symbol_tree_ptr;

  SymbolMapStack m_symbol_stack;
  SymbolMapIter m_last_elem;

  std::size_t m_id_count;

  public:
  SymbolTreeFactory();

  auto init() -> void;

  //! Insert an entry for the current level of scope.
  auto insert(std::string_view t_id) -> SymbolTreeId;

  // Manage nesting of symbols:
  auto push_scope() -> void;
  auto pop_scope() -> void;

  auto clear() -> void;
  auto retrieve() const -> SymbolTreePtr;

  virtual ~SymbolTreeFactory() = default;
};
} // namespace symbol_table::symbol_tree

#endif // ACRIS_ACRIS_SYMBOL_TABLE_SYMBOL_TREE_SYMBOL_TREE_FACTORY_HPP
