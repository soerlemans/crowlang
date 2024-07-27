#ifndef CONTEXT_VALIDATOR_HPP
#define CONTEXT_VALIDATOR_HPP

// STL Includes:
#include <unordered_map>

namespace parser::crow::context {
// Enums:
//! Possible contexts to be parsing in.
enum class Context {
  LOOP,
};

// Aliases:
using ContextMap = std::unordered_map<Context, bool>;

// Classes:
class ContextStore {
  private:
  ContextMap m_store;

  public:
  ContextStore();

  auto set(Context t_context) -> void;
  auto clear(Context t_context) -> void;

  auto get(Context t_context) -> bool;

  virtual ~ContextStore() = default;
};
} // namespace parser::crow::context

#endif // CONTEXT_VALIDATOR_HPP
