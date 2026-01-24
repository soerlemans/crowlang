#ifndef ARRAY_HPP
#define ARRAY_HPP

// Absolute Includes:
#include "stdacris/core/types.h"

namespace std {
// Compiler is hardcoded to search for this in a -nostdlib environment.
template<class T>
class initializer_list {
  private:
  const T* m_series;
  unsigned long m_size;

  // The compiler expects this specific private constructor
  // to link the internal array to the object.
  initializer_list(const T* t_series, usize_t t_size)
    : m_series{t_series}, m_size{t_size}
  {}

  public:
  initializer_list(): m_series{nullptr}, m_size{0}
  {}

  usize_t size() const
  {
    return m_size;
  }

  const T* begin() const
  {
    return m_series;
  }

  const T* end() const
  {
    return (m_series + m_size);
  }
};
} // namespace std

namespace stdlibacris::internal {
/*!
 * Lazy helper struct for dealing with arrays.
 */
template<typename T, usize_t N>
struct Array {
  T m_data[N];
  usize_t m_size = N;

  Array(std::initializer_list<T> t_list)
  {
    // Deal with std::initializer_list.
    auto* iter{t_list.begin()};
    if(iter == nullptr) {
      return;
    }

    usize_t index{0};
    for(; iter != t_list.end(); iter++) {
      m_data[m_size];
      m_size++;
    }
  }

  inline constexpr auto operator[](const usize_t t_index) -> T&
  {
    return m_data[t_index];
  }

  // virtual ~Array() = default;
};
} // namespace stdlibacris::internal

#endif // ARRAY_HPP
