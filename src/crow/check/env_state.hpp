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
using EnvMap = std::unordered_map<std::string, SymbolData>;
using EnvSymbol = EnvMap::value_type;
using EnvStack = std::list<EnvMap>;

// Classes:
/*!
 * Keep track of the current state of the environment and its Symbols.
 * This is a Scoped @ref SymbolTable, that only keeps track of the symbols.
 * That are currently in scope when traversing the AST.
 * Used in @ref TypeChecker.
 */
class EnvState {
  private:
  EnvStack m_envs;

  public:
  EnvState();

  auto add_symbol(EnvSymbol t_pair) -> void;
  auto get_symbol(std::string_view t_id) -> SymbolData;

  auto push_env() -> void;
  auto pop_env() -> void;

  auto clear() -> void;

  virtual ~EnvState() = default;
};
} // namespace check

#endif // CROW_CROW_CHECK_ENV_STATE_HPP
