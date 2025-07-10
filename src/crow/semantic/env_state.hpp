#ifndef CROW_CROW_SEMANTIC_ENV_STATE_HPP
#define CROW_CROW_SEMANTIC_ENV_STATE_HPP

// STL Includes:
#include <string>
#include <string_view>
#include <unordered_map>

// Absolute Includes:
#include "crow/diagnostic/type_error.hpp"
#include "crow/types/semantic/symbol_types.hpp"

namespace semantic {
// Using :
using symbol::SymbolData;

// Classes:
/*!
 * Keep track of the current state of the environment and its Symbols.
 * This is a Scoped @ref SymbolTable, that only keeps track of the symbols.
 * That are currently in scope when traversing the AST.
 * Used in @ref SemanticChecker.
 */
class EnvState {
  private:
  EnvStack m_envs;

  public:
  EnvState();

  auto add_symbol(EnvSymbol t_pair) -> std::pair<EnvMap::iterator, bool>;
  auto get_symbol(std::string_view t_id) const -> SymbolData;

  auto push_env() -> void;
  auto pop_env() -> void;

  auto clear() -> void;
  auto stack() const -> const EnvStack&;

  virtual ~EnvState() = default;
};
} // namespace semantic

// Functions:
auto operator<<(std::ostream& t_os, const semantic::EnvState& t_env_state)
  -> std::ostream&;

#endif // CROW_CROW_SEMANTIC_ENV_STATE_HPP
