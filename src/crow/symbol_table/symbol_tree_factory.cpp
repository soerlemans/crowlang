#include "symbol_tree_factory.hpp"

// Absolute Includes:
#include "crow/debug/log.hpp"

namespace symbol_table {
auto SymbolTreeFactory::insert(const std::string_view t_id,
                               const SymbolData& t_data) -> bool
{
  using symbol_table::SymbolMapEntry;
  using symbol_table::SymbolMapInsertResult;

  if(!m_symbol_table_ptr) {
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

  // TODO: Replace by adding an operator<<(ostream) for @ref SymbolTreeFactory.
  DBG_NOTICE("SymbolTree: ", *m_symbol_tree_ptr);

  return result.second;
}

auto SymbolTreeFactory::push_scope() -> void
{
  // Iterator to last inserted element is pushed onto the stack.
  m_symbol_stack.push(m_last_elem);
}

auto SymbolTreeFactory::pop_scope() -> void
{
  m_symbol_stack.pop();
}

auto SymbolTreeFactory::clear() -> void
{
  // Reset all the members.
  m_last_elem = {};
  m_symbol_stack = {};

  m_symbol_tree_ptr.reset();
}

auto SymbolTreeFactory::retrieve() const -> SymbolTreePtr
{
  return m_symbol_tree_ptr;
}
} // namespace symbol_table
