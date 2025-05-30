#ifndef CROW_LIB_STDPRINT_HPP
#define CROW_LIB_STDPRINT_HPP

/*!
 * @file Utilities for printing standard library containers.
 * Every output function is in its own
 */

// STL Includes:
#include <array>
#include <concepts>
#include <list>
#include <string_view>
#include <vector>

// TODO: Relocate, to stdprint directory.
namespace lib::stdprint {
//! Internal helper utilities do not use directly.
namespace detail {
template<typename T>
concept Container = requires(T t) {
  typename T::value_type;
  typename T::iterator;
  typename T::const_iterator;
  typename T::size_type;
  { t.begin() } -> std::input_iterator;
  { t.end() } -> std::input_iterator;
  { t.size() } -> std::same_as<typename T::size_type>;
};

//! Helper function which prints all sequential containers.
template<typename T>
  requires Container<T>
auto print_seq(std::ostream& t_os, const T& t_container) -> std::ostream&
{
  using namespace std::literals;

  t_os << '[';
  auto sep{""sv};
  for(auto&& elem : t_container) {
    t_os << sep << elem;

    sep = ", "sv;
  }
  t_os << ']';

  return t_os;
}
} // namespace detail

namespace vector {
//! For printing vectors.
template<typename T>
auto operator<<(std::ostream& t_os, const std::vector<T>& t_vector)
  -> std::ostream&
{
  detail::print_seq(t_os, t_vector);

  return t_os;
}
} // namespace vector

namespace array {
//
template<typename T, size_t S>
auto operator<<(std::ostream& t_os, const std::array<T, S>& t_array)
  -> std::ostream&
{
  detail::print_seq(t_os, t_array);

  return t_os;
}
} // namespace array

namespace list {
template<typename T>
auto operator<<(std::ostream& t_os, const std::list<T>& t_list) -> std::ostream&
{
  detail::print_seq(t_os, t_list);

  return t_os;
}
} // namespace list

//! Namespace that when included allows you to use all the ostream functions.
namespace all {
using namespace lib::stdprint::vector;
using namespace lib::stdprint::list;
using namespace lib::stdprint::array;
} // namespace all
} // namespace lib::stdprint

#endif // CROW_LIB_STDPRINT_HPP
