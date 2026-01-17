#ifndef ACRIS_LIB_ENUM2INT_HPP
#define ACRIS_LIB_ENUM2INT_HPP

// STL Includes:
#include <type_traits>

namespace lib {
// Functions
template<typename T>
constexpr inline auto enum2int(const T t_value) -> std::underlying_type_t<T>
{
  return static_cast<std::underlying_type_t<T>>(t_value);
}
} // namespace lib

#endif // ACRIS_LIB_ENUM2INT_HPP
