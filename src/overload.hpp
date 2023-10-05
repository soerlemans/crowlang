#ifndef CROW_OVERLOAD_HPP
#define CROW_OVERLOAD_HPP


// Overload pattern:
//! Helper struct that selects correct lambda to execute in std::visit
template<class... Ts>
struct Overload : Ts... {
  using Ts::operator()...;
};

//! Deduction guide for the Overload struct to work
template<class... Ts>
Overload(Ts...) -> Overload<Ts...>;

#endif // CROW_OVERLOAD_HPP
