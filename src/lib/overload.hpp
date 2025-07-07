#ifndef CROW_LIB_OVERLOAD_HPP
#define CROW_LIB_OVERLOAD_HPP

namespace lib {
// Overload pattern:
/*!
 *	Helper struct for overloading callables when using @ref std::visit.
 */
template<class... Ts>
struct Overload : Ts... {
  using Ts::operator()...;
};

//! Deduction guide for the overload to work.
template<class... Ts>
Overload(Ts...) -> Overload<Ts...>;
} // namespace lib

#endif // CROW_LIB_OVERLOAD_HPP
