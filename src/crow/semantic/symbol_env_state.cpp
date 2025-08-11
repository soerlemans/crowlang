#include "symbol_env_state.hpp"

// STL Includes:
#include <iomanip>
#include <ranges>
#include <sstream>

// Absolute Includes:
#include "crow/debug/log.hpp"
#include "lib/stdexcept/stdexcept.hpp"

// Macros:
#define MATCH(t_key, t_value) \
  case SymbolStatus::t_key:   \
    str = t_value;            \
    break

namespace semantic {
auto SymbolEnvState::get_value(const std::string_view t_key) const
  -> const Symbol&
{
  const auto [iter, found] = EnvState::find(t_key);

  const auto str{std::quoted(t_key)};
  if(!found) {
    using diagnostic::throw_type_error;

    // Should never happen so throw and report to user.
    throw_type_error("Identifier ", str, " is not defined.");
  }

  // Return the found Symbol.
  return {iter->second};
}

auto SymbolEnvState::get_status(const std::string_view t_key) const
  -> SymbolStatus
{
  const auto symbol{get_value(t_key)};

  return symbol.m_status;
}

auto SymbolEnvState::get_data(const std::string_view t_key) const -> SymbolData
{
  const auto symbol{get_value(t_key)};

  return symbol.m_data;
}

// Functions:
auto symbol_status2str(const SymbolStatus t_status) -> std::string_view
{
  using lib::stdexcept::throw_invalid_argument;

  std::string_view str{};

  switch(t_status) {
    MATCH(DECLARED, "declared");
    MATCH(DEFINED, "defined");

    default:
      throw_invalid_argument(
        "SymbolStatus could not be converted to std::string_view.");
      break;
  }

  return str;
}
} // namespace semantic

// Functions:
auto operator<<(std::ostream& t_os, const semantic::Symbol& t_symbol)
  -> std::ostream&
{
  using semantic::symbol_status2str;

  const auto status{symbol_status2str(t_symbol.m_status)};

  // clang-format off
  t_os << "Symbol{"
			 << "status: " << status << ", "
			 << "data: " << t_symbol.m_data
			 << "}";
  // clang-format on

  return t_os;
}
