#ifndef ACRIS_ACRIS_CONTAINER_ENV_STATE_HPP
#define ACRIS_ACRIS_CONTAINER_ENV_STATE_HPP

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

// FIXME: Use std::expected for implementation.

namespace container {
// Forward Declarations:
template<typename T>
class EnvState;

template<typename T>
inline auto print_env_state(std::ostream& t_os,
                            container::EnvState<T>& t_state);

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
 * So this data structure is only temporarily used/alive.
 *
 * @note The given @ref std::variant must be default constructible.
 */
template<typename T>
// requires IsVariant<T>::value
class EnvState {
  private:
  using PrivEnvMap = std::unordered_map<std::string, T>;
  using PrivEnvStack = std::list<PrivEnvMap>;

  PrivEnvStack m_envs;

  public:
  // Aliases:
  using EnvMap = PrivEnvMap;
  using EnvStack = PrivEnvStack;

  using Iter = typename EnvMap::iterator;
  using ConstIter = typename EnvMap::const_iterator;

  using FindResult = std::pair<Iter, bool>;
  using ConstFindResult = std::pair<ConstIter, bool>;

  using InsertResult = std::pair<Iter, bool>;

  // Methods:
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
  virtual auto find(const std::string_view t_key) -> FindResult
  {
    FindResult result{};
    result.first = Iter{};
    result.second = false;

    // We want to traverse the scopes from inner.
    // To outer so we reverse the range.
    // We need to use reverse iterators for the non-const implementation.
    auto rbegin = m_envs.rbegin();
    auto rend = m_envs.rend();
    for(auto env_iter = rbegin; env_iter != rend; ++env_iter) {
      auto& scope{*env_iter};
      auto iter{scope.find(std::string{t_key})};

      if(iter != scope.end()) {
        result.first = iter;
        result.second = true;
        break;
      }
    }

    return result;
  }

  //! Return entry and boolean if it was found.
  virtual auto find(const std::string_view t_key) const -> ConstFindResult
  {
    ConstIter pair_iter{};
    bool found{false};

    // We want to traverse the scopes from inner.
    // To outer so we reverse the range.
    for(const auto& env : m_envs | std::views::reverse) {
      const auto iter{env.find(std::string{t_key})};

      if(iter != env.end()) {
        found = true;
        pair_iter = iter;
        break;
      }
    }

    return ConstFindResult{pair_iter, found};
  }

  auto contains(std::string_view t_key) const -> bool
  {
    for(const auto& env : m_envs | std::views::reverse) {
      const auto found{env.contains(std::string{t_key})};
      if(found) {
        return true;
      }
    }

    return false;
  }

  auto is_toplevel() -> bool
  {
    // If there is only one scope left its the toplevel.
    return (m_envs.size() == 1);
  }

  virtual auto push_env() -> void
  {
    m_envs.emplace_back();
  }

  virtual auto pop_env() -> void
  {
    // We should never deallocate the toplevel scope.
    if(is_toplevel()) {
      using lib::stdexcept::throw_runtime_error;

      throw_runtime_error("Tried to call pop_back on empty list.");
    }

    m_envs.pop_back();
  }

  virtual auto clear() -> void
  {
    m_envs.clear();

    // Always make sure the global/toplevel scope is present..
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

  auto begin() noexcept -> EnvStack::iterator
  {
    return m_envs.begin();
  }

  auto end() noexcept -> EnvStack::iterator
  {
    return m_envs.end();
  }

  auto begin() const noexcept -> EnvStack::const_iterator
  {
    return m_envs.cbegin();
  }

  auto end() const noexcept -> EnvStack::const_iterator
  {
    return m_envs.cend();
  }

  auto cbegin() const noexcept -> EnvStack::const_iterator
  {
    return m_envs.cbegin();
  }

  auto cend() const noexcept -> EnvStack::const_iterator
  {
    return m_envs.cend();
  }

  virtual ~EnvState() = default;
};
} // namespace container

#endif // ACRIS_ACRIS_CONTAINER_ENV_STATE_HPP
