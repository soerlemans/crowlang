#ifndef CROW_CROW_CLIR_CLIR_BUILDER_CLIR_ENV_STATE_HPP
#define CROW_CROW_CLIR_CLIR_BUILDER_CLIR_ENV_STATE_HPP

// Absolute Includes:
#include "crow/container/env_state.hpp"
#include "crow/types/core/core.hpp"

namespace clir::clir_builder {
// Classes:
/*!
 * Keep track of the current state of the environment and its Symbols.
 * This is a Scoped @ref SymbolTable, that only keeps track of the symbols.
 * That are currently in scope when traversing the AST.
 * Used in @ref SemanticChecker.
 */
class ClirEnvState : public container::EnvState<types::core::TypeVariant> {
  private:
  using TypeVariant = types::core::TypeVariant;
  using BaseEnvState = container::EnvState<TypeVariant>;

  public:
  ClirEnvState();

  //! Get means it is required and if we dont find it error.
  auto get(const std::string_view t_key) const -> TypeVariant;

  friend auto operator<<(std::ostream& t_os, const ClirEnvState& t_state)
    -> std::ostream&;

  virtual ~ClirEnvState() = default;
};
} // namespace clir::clir_builder

#endif // CROW_CROW_CLIR_CLIR_BUILDER_CLIR_ENV_STATE_HPP
