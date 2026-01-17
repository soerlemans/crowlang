#include "context_store.hpp"

namespace parser::acris::context {
ContextStore::ContextStore(): m_store{}
{}

auto ContextStore::set(const Context t_context) -> void
{
  m_store[t_context] = true;
}

auto ContextStore::clear(const Context t_context) -> void
{
  m_store[t_context] = false;
}

auto ContextStore::get(const Context t_context) -> bool
{
  bool enabled{false};

  const auto iter{m_store.find(t_context)};
  if(iter != m_store.end()) {
    enabled = iter->second;
  }

  return enabled;
}
} // namespace parser::acris::context
