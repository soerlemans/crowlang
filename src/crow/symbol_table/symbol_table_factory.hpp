#ifndef CROW_CROW_SYMBOL_TABLE_SYMBOL_TABLE_FACTORY_HPP
#define CROW_CROW_SYMBOL_TABLE_SYMBOL_TABLE_FACTORY_HPP

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

namespace symbol_table {
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
template<typename RegisterType>
class SymbolTableFactory {
  private:
  SymbolMapIter m_last_elem;
  SymbolMapStack m_symbol_stack;

  SymbolTreePtr m_symbol_tree_ptr;

  public:
  SymbolTableFactory() = default;

  auto init() -> void;

  //! Insert symbol to the current level of scoping.
  auto insert(std::string_view t_id, const T& t_value) -> bool

  {
    using symbol_table::SymbolMapEntry;
    using symbol_table::SymbolMapInsertResult;

    if(!m_symbol_tree_ptr) {
      m_symbol_tree_ptr = std::make_shared<SymbolTree>();
    }

    const SymbolMapEntry entry{
      std::string{t_id},
      {t_data, {}}
    };

    // Return result of insertion.
    SymbolMapInsertResult result{};
    if(m_symbol_stack.empty()) {
      result = m_symbol_tree_ptr->insert(entry);
    } else {
      auto& top_iter{m_symbol_stack.top()};

      result = m_symbol_tree_ptr->insert(top_iter, entry);
    }
    m_last_elem = result.first;

    // TODO: Replace by adding an operator<<(ostream) for @ref
    // SymbolTableFactory.
    DBG_NOTICE("SymbolTable: ", *m_symbol_tree_ptr);

    return result.second;
  }

  // Manage nesting of symbols:
  auto push_scope() -> void
  {
    // Iterator to last inserted element is pushed onto the stack.
    m_symbol_stack.push(m_last_elem);
  }

  auto pop_scope() -> void
  {
    m_symbol_stack.pop();
  }

  auto clear() -> void
  {
    // Reset all the members.
    m_last_elem = {};
    m_symbol_stack = {};

    m_symbol_tree_ptr.reset();
  }

  auto retrieve() const -> SymbolTreePtr
  {
    return m_symbol_tree_ptr;
  }

  virtual ~SymbolTableFactory() = default;
};

// Methods:
auto SymbolTablePtr::init() -> void
{
  clear();
}


} // namespace symbol_table


#endif // CROW_CROW_SYMBOL_TABLE_SYMBOL_TABLE_FACTORY_HPP
