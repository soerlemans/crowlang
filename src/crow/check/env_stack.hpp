#ifndef CROW_CROW_CHECK_ENV_STACK_HPP
#define CROW_CROW_CHECK_ENV_STACK_HPP

// STL Includes:
#include <map>
#include <string>
#include <string_view>

// Absolute Includes:
#include "crow/exception/type_error.hpp"

// Local Includes:
#include "symbol_types.hpp"

namespace check {
// Aliases:
using Symbol = std::pair<std::string, SymbolData>;
using Env = std::map<std::string, SymbolData>;

// Classes:
class EnvStack {
  private:
  std::list<Env> m_envs;

  public:
  EnvStack();

  auto add_symbol(std::string_view t_id, SymbolData t_data) -> void;
  auto get_symbol(std::string_view t_id) -> SymbolData;

  auto push_env() -> void;
  auto pop_env() -> void;

  auto clear() -> void;

  virtual ~EnvStack() = default;
};
} // namespace check

#endif // CROW_CROW_CHECK_ENV_STACK_HPP
