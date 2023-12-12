#ifndef CROW_LIB_ENUM2INT_HPP
#define CROW_LIB_ENUM2INT_HPP

// STL Includes:
#include <type_traits>


// Functions
template<typename T>
constexpr auto enum2int(const T t_value) -> std::underlying_type_t<T>
{
  return static_cast<std::underlying_type_t<T>>(t_value);
}

#endif // CROW_LIB_ENUM2INT_HPP
