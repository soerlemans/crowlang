#ifndef ARRAY_HPP
#define ARRAY_HPP

// Absolute Includes:
#include "stdacris/core/types.h"

namespace stdlibacris::internal {
/*!
 * Lazy helper struct for dealing with arrays.
 */
template<typename T, usize_t N>
struct Array {
  T m_data[N];
  usize_t m_size = N;

  inline constexpr auto operator[](const usize_t t_index) -> T&
  {
    return m_data[t_index];
  }
};
} // namespace stdlibacris::internal

#endif // ARRAY_HPP
