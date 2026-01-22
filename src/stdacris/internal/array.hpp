#ifndef ARRAY_HPP
#define ARRAY_HPP

// Absolute Includes:
#include "stdacris/core/types.h"

namespace stdlibacris::internal {
template<typename T, usize_t N>
struct Array {
  T m_data[N];
  usize_t m_size = N;
};

} // namespace stdlibacris::internal

#endif // ARRAY_HPP
