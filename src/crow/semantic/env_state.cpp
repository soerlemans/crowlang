#include "env_state.hpp"

// STL Includes:
#include <algorithm>
#include <any>
#include <iomanip>
#include <ranges>
#include <sstream>

// Absolute Includes:
#include "crow/debug/log.hpp"

namespace semantic {
// Using Statements:
using diagnostic::type_error;

// Public Methods:
EnvState::EnvState(): m_envs{}
{
  // Always initialize the global scope.
  // Or esle we will get lookup errors.
  m_envs.emplace_back();
}

auto EnvState::add_symbol(const EnvSymbol t_pair)
  -> std::pair<EnvMap::iterator, bool>
{
  auto& current_scope{m_envs.back()};
  const auto result{current_scope.insert(t_pair)};

  return result;
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
    // Should never happen so throw.
    type_error("Identifier ", str, " is not defined.");
  }

  return data;
}

auto EnvState::push_env() -> void
{
  m_envs.emplace_back();
}

auto EnvState::pop_env() -> void
{
  m_envs.pop_back();
}

auto EnvState::clear() -> void
{
  m_envs.clear();

  // Always make sure the Global scope exists
  m_envs.emplace_back();
}

auto EnvState::stack() const -> const EnvStack&
{
  return m_envs;
}
} // namespace semantic

// Functions:
auto operator<<(std::ostream& t_os, const semantic::EnvStack& t_envs)
  -> std::ostream&
{
  using namespace std::literals::string_view_literals;

  auto sep{""sv};
  auto env_index{0};
  for(const auto& env : t_envs) {
    t_os << sep << env_index << ":[";

    auto sep_elem{""sv};
    for(const auto& elem : env) {
      const auto& [first, second] = elem;

      t_os << sep_elem << '{' << first << ':' << second << '}';

      sep_elem = ", "sv;
    }
    t_os << ']';

    sep = ", "sv;
    env_index++;
  }

  return t_os;
}

auto operator<<(std::ostream& t_os, const semantic::EnvState& t_env_state)
  -> std::ostream&
{
  t_os << t_env_state.stack();

  return t_os;
}
