#ifndef CROW_CROW_CLIR_CLIR_BUILDER_CLIR_ENV_STATE_HPP
#define CROW_CROW_CLIR_CLIR_BUILDER_CLIR_ENV_STATE_HPP

// STL Includes:
#include <iomanip>
#include <ranges>
#include <sstream>
#include <variant>

// Absolute Includes:
#include "crow/clir/clir.hpp"
#include "crow/container/env_state.hpp"
#include "crow/types/core/core.hpp"
#include "lib/stdexcept/stdexcept.hpp"

namespace clir::clir_builder {
// Classes:
/*!
 * TODO: Document.
 */
template<typename T>
class ClirEnvState : public container::EnvState<T> {
  private:
  using BaseEnvState = container::EnvState<T>;

  public:
  ClirEnvState(): BaseEnvState{}
  {}

  //! Get means it is required and if we dont find it error.
  auto get(const std::string_view t_key) const -> T
  {
    const auto [result, found] = BaseEnvState::find(t_key);

    if(!found) {
      using lib::stdexcept::runtime_exception;

      // Should never happen so throw and report to user.
      const auto str{std::quoted(t_key)};
      runtime_exception("Identifier ", str, " is not defined.");
    }

    // Return the found entry.
    return {result};
  }

  friend auto operator<<(std::ostream& t_os, const ClirEnvState& t_state)
    -> std::ostream&
  {
    const auto& base{static_cast<const ClirEnvState::BaseEnvState&>(t_state)};

    // Call formatting for base class.
    // FIXME: Not working right now, base class cant find IrVariant.
    // operator<<(). operator<<(t_os, base);

    return t_os;
  }

  virtual ~ClirEnvState() = default;
};
} // namespace clir::clir_builder

#endif // CROW_CROW_CLIR_CLIR_BUILDER_CLIR_ENV_STATE_HPP
