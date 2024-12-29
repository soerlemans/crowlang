#ifndef CROW_CROW_CHECK_ENV_STATE_HPP
#define CROW_CROW_CHECK_ENV_STATE_HPP

// STL Includes:
#include <string>
#include <string_view>
#include <unordered_map>

// Absolute Includes:
#include "crow/exception/type_error.hpp"

// Local Includes:
#include "symbol/symbol_types.hpp"

namespace check {
// Using Declarations:
using symbol::SymbolData;

// Aliases:
using Symbol = std::pair<std::string, SymbolData>;
using Env = std::unordered_map<std::string, SymbolData>;

// Classes:
/*!
 * Keep track of the current state of the environment and its Symbols.
 * This construct merely keeps track of the symbols that are in scope.
 * When we use the @ref TypeChecker.
 */
class EnvState {
  private:
  std::list<Env> m_envs;

  public:
  EnvState();

  auto add_symbol(std::string_view t_id, SymbolData t_data) -> void;
  auto get_symbol(std::string_view t_id) -> SymbolData;

  auto push_env() -> void;
  auto pop_env() -> void;

  auto clear() -> void;

  virtual ~EnvState() = default;
};
} // namespace check

#endif // CROW_CROW_CHECK_ENV_STATE_HPP
