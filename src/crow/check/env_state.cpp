#include "env_state.hpp"

// STL Includes:
#include <algorithm>
#include <any>
#include <iomanip>
#include <ranges>

// Absolute Includes:
#include "crow/debug/log.hpp"

namespace check {
// Using Statements:
using exception::type_error;

// Public Methods:
EnvState::EnvState(): m_envs{}
{
  // Always initialize the global scope.
  // Or esle we will get lookup errors.
  m_envs.emplace_back();
}

auto EnvState::add_symbol(const EnvSymbol t_pair) -> void
{
  const auto result{m_envs.back().insert(t_pair)};
  if(!result.second) {
    // TODO: Add name of already defined symbol to exception.
    throw std::invalid_argument{"Symbol already defined in current scope."};
  }
}

auto EnvState::get_symbol(const std::string_view t_id) const -> SymbolData
{
  bool found{false};
  SymbolData data;
  const auto str{std::quoted(t_id)};

  // We want to traverse the scopes from inner to outer so we reverse the range.
  for(const auto& env : m_envs | std::views::reverse) {
    const auto iter{env.find(std::string{t_id})};

    if(iter != env.end()) {
      found = true;
      data = iter->second;

      DBG_INFO("Found Symbol ", str, " of type ", data, " in Env!");
      break;
    }
  }

  if(!found) {
    type_error("Identifier ", str, " is not defined.");
  }

  return data;
}

auto EnvState::push_env() -> void
{}

auto EnvState::pop_env() -> void
{}

auto EnvState::clear() -> void
{
  m_envs.clear();

  // Always make sure the Global scope exists
  m_envs.emplace_back();
}
} // namespace check
