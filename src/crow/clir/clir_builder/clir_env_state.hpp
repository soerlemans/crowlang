#ifndef CROW_CROW_CLIR_CLIR_BUILDER_CLIR_ENV_STATE_HPP
#define CROW_CROW_CLIR_CLIR_BUILDER_CLIR_ENV_STATE_HPP

#include "crow/types/core/core.hpp"

namespace clir::clir_builder {
// Classes:
/*!
 * Keep track of the current state of the environment.
 * Functions, variables, structs, etc.
 * That are currently in scope when traversing the AST.
 * Used for lookup of temporary SSA vars and function signatures.
 */
class ClirEnvState {
  private:
  // Aliases:
  using EnvMap = std::unordered_map<std::string, TypeVariant>;
  using EnvValue = EnvMap::value_type;
  using EnvStack = std::list<EnvMap>;

  EnvStack m_envs;

  public:
  ClirEnvState();

  auto add_symbol(EnvValue t_pair) -> std::pair<EnvMap::iterator, bool>;
  auto get_symbol(std::string_view t_id) const -> SymbolData;

  auto push_env() -> void;
  auto pop_env() -> void;

  auto clear() -> void;
  auto stack() const -> const EnvStack&;

  virtual ~ClirEnvState() = default;
};

// Functions:
auto operator<<(std::ostream& t_os, const semantic::EnvStack& t_envs)
  -> std::ostream&;
auto operator<<(std::ostream& t_os, const semantic::ClirEnvState& t_env_state)
  -> std::ostream&;


} // namespace clir::clir_builder

#endif // CROW_CROW_CLIR_CLIR_BUILDER_CLIR_ENV_STATE_HPP
