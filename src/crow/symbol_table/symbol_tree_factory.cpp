#include "symbol_tree_factory.hpp"

// Absolute Includes:
#include "crow/debug/log.hpp"

namespace symbol_table {

SymbolTreeFactory::SymbolTreeFactory()
  : m_symbol_tree_ptr{}, m_symbol_stack{}, m_last_elem{}, m_id_count{0}
{}

auto SymbolTreeFactory::init() -> void
{
  if(!m_symbol_tree_ptr) {
    m_symbol_tree_ptr = std::make_shared<SymbolTree>();
  }
}

auto SymbolTreeFactory::insert(const std::string_view t_id) -> bool
{
  using symbol_table::SymbolMapEntry;
  using symbol_table::SymbolMapInsertResult;

  // Ensure that the symbol tree ptr exists.
  init();

  const SymbolMapEntry entry{
    std::string{t_id},
    {m_id_count, {}}
  };

  // Return result of insertion.
  SymbolMapInsertResult result{};
  if(m_symbol_stack.empty()) {
    // Check if insertion failed and throw.
    result = m_symbol_tree_ptr->insert(entry);
  } else {
    auto& top_iter{m_symbol_stack.top()};

    // Check if insertion failed and throw.
    result = m_symbol_tree_ptr->insert(top_iter, entry);
  }

  // Perform post insertion updates.
  m_last_elem = result.first;
  m_id_count++;

  // FIXME: Remove debug line.
  // DBG_NOTICE("SymbolTree: ", *m_symbol_tree_ptr);

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
  m_id_count = 0;

  m_last_elem = {};
  m_symbol_stack = {};

  m_symbol_tree_ptr.reset();
}

auto SymbolTreeFactory::retrieve() const -> SymbolTreePtr
{
  return m_symbol_tree_ptr;
}
} // namespace symbol_table
