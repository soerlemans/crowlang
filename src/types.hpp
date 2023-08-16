#ifndef NEWLANG_TYPES_HPP
#define NEWLANG_TYPES_HPP

// STL Includes:
#include <cstdint>
#include <string>
#include <string_view>
#include <type_traits>


// Aliases:
// using string = std::string;
// using string_view = std::string_view;

// Integer type aliases:
using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;

using i8 = std::int8_t;
using i16 = std::int16_t;
using i32 = std::int32_t;
using i64 = std::int64_t;


// Functions
template<typename T>
constexpr auto enum2int(const T t_value) -> std::underlying_type_t<T>
{
  return static_cast<std::underlying_type_t<T>>(t_value);
}

#endif // NEWLANG_TYPES_HPP
