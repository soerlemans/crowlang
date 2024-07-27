#include "context_guard.hpp"

namespace parser::crow::context {
ContextGuard::ContextGuard(const Context t_context, ContextStore& t_store)
  : m_context{t_context}, m_store{t_store}
{
  m_store.set(m_context);
}

ContextGuard::~ContextGuard()
{
  m_store.clear(m_context);
}
} // namespace parser::crow::context
