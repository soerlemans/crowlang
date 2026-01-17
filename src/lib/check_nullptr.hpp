#ifndef ACRIS_LIB_CHECK_NULLPTR_HPP
#define ACRIS_LIB_CHECK_NULLPTR_HPP

// STL Includes:
#include <format>
#include <string>
#include <string_view>

// Absolute Includes:
#include "lib/stdexcept/unexpected_nullptr.hpp"

// Macros:
// TODO: Potentially encode, position information.
// TODO: Potentially rename ASSERT_NULLPTR.
#define CHECK_NULLPTR(t_ptr) \
  lib::check_nullptr(t_ptr, std::format(R"(Caught nullptr for "{}".)", #t_ptr));

namespace lib {
// TODO: Add more strict typechecking for pointer types.
template<typename T>
constexpr inline auto check_nullptr(T t_ptr, const std::string t_msg) -> void
{
  using lib::stdexcept::throw_unexpected_nullptr;

  // Check for nullptr and else throw.
  if(t_ptr == nullptr) {
    throw_unexpected_nullptr(t_msg);
  }
}
} // namespace lib

#endif // ACRIS_LIB_CHECK_NULLPTR_HPP
