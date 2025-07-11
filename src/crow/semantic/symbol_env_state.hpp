#ifndef CROW_CROW_SEMANTIC_SYMBOL_ENV_STATE_HPP
#define CROW_CROW_SEMANTIC_SYMBOL_ENV_STATE_HPP

// STL Includes:
#include <iomanip>
#include <sstream>
#include <string>
#include <string_view>
#include <unordered_map>

// Absolute Includes:
#include "crow/container/env_state.hpp"
#include "crow/diagnostic/diagnostic.hpp"
#include "crow/types/semantic/semantic.hpp"

namespace semantic {
// Classes:
/*!
 * Keep track of the current state of the environment and its Symbols.
 * This is a Scoped @ref SymbolTable, that only keeps track of the symbols.
 * That are currently in scope when traversing the AST.
 * Used in @ref SemanticChecker.
 */
class SymbolEnvState : public container::EnvState<symbol::SymbolData> {
  private:
  using SymbolData = symbol::SymbolData;
  using BaseEnvState = container::EnvState<SymbolData>;

  public:
  SymbolEnvState();

  //! Get means it is required and if we dont find it error.
  auto get(const std::string_view t_key) const -> SymbolData;

  friend auto operator<<(std::ostream& t_os, const SymbolEnvState& t_env_state)
    -> std::ostream&;

  virtual ~SymbolEnvState() = default;
};
} // namespace semantic

// Functions:

#endif // CROW_CROW_SEMANTIC_SYMBOL_ENV_STATE_HPP
