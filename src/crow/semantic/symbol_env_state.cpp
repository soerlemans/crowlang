#include "symbol_env_state.hpp"

// STL Includes:
#include <iomanip>
#include <ranges>
#include <sstream>

// Absolute Includes:
#include "crow/debug/log.hpp"

namespace semantic {
SymbolEnvState::SymbolEnvState(): BaseEnvState{}
{}

auto SymbolEnvState::get_value(const std::string_view t_key) const -> SymbolData
{
  const auto [iter, found] = EnvState::find(t_key);

  const auto str{std::quoted(t_key)};
  if(!found) {
    using diagnostic::throw_type_error;

    // Should never happen so throw and report to user.
    throw_type_error("Identifier ", str, " is not defined.");
  }

  // Return the found SymbolData.
  SymbolData data{iter->second};
  DBG_INFO("Found Symbol ", str, " of type ", data, " in SymbolEnv!");
  return {data};
}
} // namespace semantic
