#include "clir_env_state.hpp"

// STL Includes:
#include <iomanip>
#include <ranges>
#include <sstream>

// Absolute Includes:
#include "lib/stdexcept/stdexcept.hpp"

namespace clir::clir_builder {
ClirEnvState::ClirEnvState(): BaseEnvState{}
{}

auto ClirEnvState::get(const std::string_view t_key) const -> TypeVariant
{
  const auto [variant, found] = EnvState::find(t_key);

  const auto str{std::quoted(t_key)};
  if(!found) {
    using lib::stdexcept::runtime_exception;

    // Should never happen so throw and report to user.
    runtime_exception("Identifier ", str, " is not defined.");
  }

  // Return the found TypeVariant.
  return {variant};
}

auto operator<<(std::ostream& t_os, const ClirEnvState& t_state)
  -> std::ostream&
{
  const auto& base{static_cast<const ClirEnvState::BaseEnvState&>(t_state)};

  // Call formatting for base class.
  // FIXME: Not working right now, base class cant find TypeVariant
  // operator<<(). operator<<(t_os, base);

  return t_os;
}
} // namespace clir::clir_builder
