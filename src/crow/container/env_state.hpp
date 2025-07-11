#ifndef CROW_CROW_CONTAINER_ENV_STATE_HPP
#define CROW_CROW_CONTAINER_ENV_STATE_HPP

// STL Includes:
#include <iomanip>
#include <iostream>
#include <list>
#include <ranges>
#include <string>
#include <string_view>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <variant>

// Absolute Includes:
#include "lib/stdexcept/stdexcept.hpp"

namespace container {
// Structs:
//! Primary template defaults to false.
template<typename T>
struct IsVariant : std::false_type {};

//! Partial specialization matches std::variant with any types.
template<typename... Args>
struct IsVariant<std::variant<Args...>> : std::true_type {};

// Classes:
/*!
 * Keep track of the current state of the environment.
 * Functions, variables, structs, etc.
 * That are currently in scope when traversing the AST.
 * Used for lookup of temporary SSA vars and function signatures.
 *
 * @note the give @ref std::variant must be default constructible.
 */
template<typename T>
// requires IsVariant<T>::value
class EnvState {
  protected:
  using EnvMap = std::unordered_map<std::string, T>;
  using EnvStack = std::list<EnvMap>;
  using FindResult = std::pair<T, bool>;
  using InsertResult = std::pair<typename EnvMap::iterator, bool>;

  private:
  EnvStack m_envs;

  public:
  EnvState()
  {
    // Always initialize the global scope.
    // Or else we will get lookup errors.
    m_envs.emplace_back();
  }

  virtual auto insert(const EnvMap::value_type& t_value)
    -> std::pair<typename EnvMap::iterator, bool>
  {
    auto& current_scope{m_envs.back()};
    const auto result{current_scope.insert(t_value)};

    return result;
  }

  //! Return entry and boolean if it was found.
  virtual auto find(const std::string_view t_key) const -> FindResult
  {
    bool found{false};
    T value{};

    // We want to traverse the scopes from inner.
    // To outer so we reverse the range.
    for(const auto& env : m_envs | std::views::reverse) {
      const auto iter{env.find(std::string{t_key})};

      if(iter != env.end()) {
        found = true;
        value = iter->second;
        break;
      }
    }

    return {value, found};
  }

  virtual auto push_env() -> void
  {
    m_envs.emplace_back();
  }

  virtual auto pop_env() -> void
  {
    if(m_envs.empty()) {
      using lib::stdexcept::runtime_exception;

      runtime_exception("Tried to call pop_back on empty list.");
    }

    m_envs.pop_back();
  }

  virtual auto clear() -> void
  {
    m_envs.clear();

    // Always make sure the Global scope exists
    m_envs.emplace_back();
  }

  friend auto operator<<(std::ostream& t_os, const EnvState<T>& t_state)
    -> std::ostream&
  {
    using namespace std::literals::string_view_literals;

    t_os << "EnvState{";

    auto sep{""sv};
    auto env_index{0};
    for(const auto& env : t_state.m_envs) {
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

    t_os << "}";

    return t_os;
  }

  virtual ~EnvState() = default;
};
} // namespace container

#endif // CROW_CROW_CONTAINER_ENV_STATE_HPP
