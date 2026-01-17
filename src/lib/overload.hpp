#ifndef ACRIS_LIB_OVERLOAD_HPP
#define ACRIS_LIB_OVERLOAD_HPP

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

#endif // ACRIS_LIB_OVERLOAD_HPP
