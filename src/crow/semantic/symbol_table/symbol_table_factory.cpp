#include "symbol_table_factory.hpp"

// Absolute Includes:
#include "crow/debug/log.hpp"

namespace semantic::symbol_table {
auto SymbolTableFactory::add_symbol(const std::string_view t_id,
                                    const SymbolData& t_data) -> bool
{
  using symbol_table::SymbolMapEntry;
  using symbol_table::SymbolMapInsertResult;

  if(!m_symbol_table_ptr) {
    m_symbol_table_ptr = std::make_shared<SymbolTable>();
  }

  const SymbolMapEntry entry{
    std::string{t_id},
    {t_data, {}}
  };

  // Return result of insertion.
  SymbolMapInsertResult result{};
  if(m_symbol_stack.empty()) {
    result = m_symbol_table_ptr->insert(entry);
  } else {
    auto& top_iter{m_symbol_stack.top()};

    result = m_symbol_table_ptr->insert(top_iter, entry);
  }
  m_last_elem = result.first;

  // TODO: Replace by adding an operator<<(ostream) for @ref SymbolTableFactory.
  DBG_NOTICE("SymbolTable: ", *m_symbol_table_ptr);

  return result.second;
}

auto SymbolTableFactory::push_scope() -> void
{
  // Iterator to last inserted element is pushed onto the stack.
  m_symbol_stack.push(m_last_elem);
}

auto SymbolTableFactory::pop_scope() -> void
{
  m_symbol_stack.pop();
}

auto SymbolTableFactory::clear() -> void
{
  // Reset all the members.
  m_last_elem = {};
  m_symbol_stack = {};

  m_symbol_table_ptr.reset();
}

auto SymbolTableFactory::retrieve() const -> SymbolTablePtr
{
  return m_symbol_table_ptr;
}
} // namespace semantic::symbol_table
