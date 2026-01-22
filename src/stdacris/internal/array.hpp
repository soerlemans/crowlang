#ifndef ARRAY_HPP
#define ARRAY_HPP

namespace stdlibacris::internal {
template<typename T, std::size_t N>
struct Array {
  T m_data[N];
  std::size_t m_size = N;
};

} // namespace stdlibacris::internal

#endif // ARRAY_HPP
