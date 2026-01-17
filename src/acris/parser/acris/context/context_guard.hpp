#ifndef ACRIS_ACRIS_PARSER_ACRIS_CONTEXT_CONTEXT_GUARD_HPP
#define ACRIS_ACRIS_PARSER_ACRIS_CONTEXT_CONTEXT_GUARD_HPP

// Local Includes:
#include "context_store.hpp"

namespace parser::acris::context {
/*!
 * Convienence class that is used to manage a context by using object lifetime.
 * This is used for example to prevent keywords like `break`, `continue`, etc.
 * From being used outside of loops.
 */
class ContextGuard {
  private:
  Context m_context;
  ContextStore& m_store;

  public:
  ContextGuard(Context t_context, ContextStore& t_store);

  virtual ~ContextGuard();
};
} // namespace parser::acris::context

#endif // ACRIS_ACRIS_PARSER_ACRIS_CONTEXT_CONTEXT_GUARD_HPP
