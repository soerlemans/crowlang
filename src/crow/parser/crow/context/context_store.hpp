#ifndef CROW_CROW_PARSER_CROW_CONTEXT_CONTEXT_STORE_HPP
#define CROW_CROW_PARSER_CROW_CONTEXT_CONTEXT_STORE_HPP

// STL Includes:
#include <unordered_map>

namespace parser::crow::context {
// Enums:
//! Possible contexts to be parsing in.
enum class Context {
  LOOP,
  METHOD,
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

#endif // CROW_CROW_PARSER_CROW_CONTEXT_CONTEXT_STORE_HPP
