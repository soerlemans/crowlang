#ifndef CROW_CROW_CHECK_ENV_STACK_HPP
#define CROW_CROW_CHECK_ENV_STACK_HPP

// STL Includes:
#include <string>
#include <string_view>
#include <unordered_map>

// Absolute Includes:
#include "crow/exception/type_error.hpp"

// Local Includes:
#include "symbol/symbol_types.hpp"

namespace check {
// Aliases:
using Symbol = std::pair<std::string, SymbolData>;
using Env = std::unordered_map<std::string, SymbolData>;

// Classes:
/*!
 * Keep track of the current state of the environment and its Symbols..
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

#endif // CROW_CROW_CHECK_ENV_STACK_HPP
