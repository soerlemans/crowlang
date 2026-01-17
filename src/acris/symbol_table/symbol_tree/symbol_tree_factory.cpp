#include "symbol_tree_factory.hpp"

// STL Includes:
#include <sstream>

// Absolute Includes:
#include "acris/debug/log.hpp"
#include "lib/stdexcept/stdexcept.hpp"

namespace symbol_table::symbol_tree {
SymbolTreeFactory::SymbolTreeFactory()
  : m_symbol_tree_ptr{}, m_symbol_stack{}, m_last_elem{}, m_id_count{0}
{}

auto SymbolTreeFactory::init() -> void
{
  if(!m_symbol_tree_ptr) {
    m_symbol_tree_ptr = std::make_shared<SymbolTree>();
  }
}

auto SymbolTreeFactory::insert(const std::string_view t_id) -> SymbolTreeId
{
  // Ensure that the symbol tree ptr exists.
  init();

  const auto symbol_id{m_id_count};
  const SymbolMapEntry entry{
    std::string{t_id},
    {symbol_id, {}}
  };

  // Return result of insertion.
  SymbolTreeResult result{};
  if(m_symbol_stack.empty()) {
    // Check if insertion failed and throw.
    result = m_symbol_tree_ptr->insert_toplevel(entry);
  } else {
    auto& top_iter{m_symbol_stack.top()};

    // Check if insertion failed and throw.
    result = m_symbol_tree_ptr->insert(top_iter, entry);
  }

  if(result) {
    // Perform post insertion updates.
    m_last_elem = result.value();
    m_id_count++;
  } else {
    using lib::stdexcept::throw_invalid_argument;

    std::stringstream ss{};
    ss << std::format(R"(Insertion failed for id "{}" error: )", t_id);
    ss << result.error();

    throw_invalid_argument(ss.str());
  }

  return symbol_id;
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
} // namespace symbol_table::symbol_tree
