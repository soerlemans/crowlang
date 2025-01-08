#ifndef SYMBOL_TABLE_FACTORY_HPP
#define SYMBOL_TABLE_FACTORY_HPP

// STL Includes:
#include <memory>
#include <stack>

// Local includes:
#include "symbol_table.hpp"

/*!
 * @file
 *
 * We do not use @ref std::unordered_map as insertion can trigger a rehash.
 * Rehashing invalidates iterators.
 * Which breaks the @ref SymbolMapStack which keeps track of the construction.
 * Using iterators, until this issue is addressed/fixed use @ref std::map.
 * For @ref SymbolTable.
 *
 * Alternatively we could use @ref std::unorederd_map.
 * And instead use indirect references by using a @ref std::stack<std::string>.
 * Which keeps track of the current ID nesting.
 */

namespace semantic::symbol_table {
// Aliases:
/*!
 * Used to construct the nested structure of the @ref SymbolTable.
 * Very similar to @ref EnvStack.
 * But the goal is to not depend on @ref EnvStack.
 * A better construction should be possible, reconsider soon.
 */
using SymbolMapStack = std::stack<SymbolMap::iterator>;

// Classes:
/*!
 */
class SymbolTableFactory {
  private:
  SymbolMapIter m_last_elem;
  SymbolMapStack m_symbol_stack;

  SymbolTablePtr m_symbol_table_ptr;

  public:
  SymbolTableFactory() = default;

  //! Add symbol to current level of nesting.
  auto add_symbol(std::string_view t_id, const SymbolData& t_data) -> bool;

  // Manage nesting of symbols:
  auto push_scope() -> void;
  auto pop_scope() -> void;

  auto clear() -> void;
  auto retrieve() const -> SymbolTablePtr;

  virtual ~SymbolTableFactory() = default;
};

} // namespace semantic::symbol_table


#endif // SYMBOL_TABLE_FACTORY_HPP
