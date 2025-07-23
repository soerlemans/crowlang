#ifndef CROW_CROW_MIR_MIR_BUILDER_MIR_ENV_STATE_HPP
#define CROW_CROW_MIR_MIR_BUILDER_MIR_ENV_STATE_HPP

// STL Includes:
#include <iomanip>
#include <ranges>
#include <sstream>
#include <variant>

// Absolute Includes:
#include "crow/container/env_state.hpp"
#include "crow/mir/mir.hpp"
#include "crow/types/core/core.hpp"
#include "lib/stdexcept/stdexcept.hpp"

// FIXME: Just realized, our IR only has two scopes.
// Global and a temp var in a function body or all other blocks.
// Since we have a var id, these effectively never clash.
// So we do not need a list of nested scopes.
// So we can optimize this away by just using one unordered_map<>.
// And perform lookups that way.
// Maybe this class has some utility for debugging?
// For now just leave as is as it works, and atm fixing this design mistake.
// Is not pressing.

namespace mir::mir_builder {
// Classes:
/*!
 * TODO: Document.
 */
template<typename T>
class MirEnvState : public container::EnvState<T> {
  private:
  using BaseEnvState = container::EnvState<T>;

  public:
  MirEnvState(): BaseEnvState{}
  {}

  auto lookup(const std::string_view t_key) -> BaseEnvState::Iter
  {
    const auto [iter, found] = BaseEnvState::find(t_key);

    if(!found) {
      using lib::stdexcept::throw_runtime_exception;

      // Should never happen so throw and report to user.
      const auto str{std::quoted(t_key)};
      throw_runtime_exception("Identifier ", str, " is not defined.");
    }

    return {iter};
  }

  //! Get means it is required and if we dont find it error.
  auto get_value(const std::string_view t_key) -> T
  {
    const auto iter{lookup(t_key)};

    return {iter->second};
  }

  //! Get means it is required and if we dont find it error.
  auto update(const std::string_view t_key, const T& t_value) -> void
  {
    auto iter{lookup(t_key)};

    // Update the value in place.
    iter->second = t_value;
  }

  virtual ~MirEnvState() = default;
};
} // namespace mir::mir_builder

#endif // CROW_CROW_MIR_MIR_BUILDER_MIR_ENV_STATE_HPP
