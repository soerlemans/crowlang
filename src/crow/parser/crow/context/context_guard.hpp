#ifndef CONTEXT_GUARD_HPP
#define CONTEXT_GUARD_HPP

// Local Includes:
#include "context_store.hpp"

namespace parser::crow::context {
/*!
 * Convienence class that is used to manage a context by using object lifetime.
 */
class ContextGuard {
  private:
  Context m_context;
  ContextStore& m_store;

  public:
  ContextGuard(Context t_context, ContextStore& t_store);

  virtual ~ContextGuard();
};
} // namespace parser::crow::context

#endif // CONTEXT_GUARD_HPP
