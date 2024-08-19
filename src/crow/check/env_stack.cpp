#include "env_stack.hpp"

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

// Methods:
EnvStack::EnvStack(): m_envs{}
{
  // Always initialize the global scope
  m_envs.emplace_back();
}

auto EnvStack::add_symbol(const std::string_view t_id, const SymbolData t_data)
  -> void
{
  Symbol pair{t_id, t_data};

  const auto result{m_envs.back().insert(pair)};
  if(!result.second) {
    // TODO: Throw exception, that name was already defined
  }
}

auto EnvStack::get_symbol(const std::string_view t_id) -> SymbolData
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

auto EnvStack::push_env() -> void
{}

auto EnvStack::pop_env() -> void
{}

auto EnvStack::clear() -> void
{
  m_envs.clear();

  // Always make sure the Global scope exists
  m_envs.emplace_back();
}
} // namespace check
