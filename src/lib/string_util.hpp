#ifndef ACRIS_LIB_STRING_UTIL_HPP
#define ACRIS_LIB_STRING_UTIL_HPP

// STL Includes:
#include <cctype>
#include <string>

namespace lib {
/*!
 * Strip all whitespace the start of a string in place.
 */
constexpr inline auto strip_whitespace(std::string& t_str) -> void
{
  std::size_t index = 0;
  for(const auto ch : t_str) {
    const auto uch{static_cast<unsigned char>(ch)};
    if(std::isspace(uch)) {
      index++;
    } else {
      break;
    }
  }

  // Warning this does not deallocate, the whitespace bytes.
  // Just moves the start.
  t_str.erase(0, index);
}

/*!
 * Trim all trailing whitespace from a string in place.
 */
constexpr inline auto trim_whitespace(std::string& t_str) -> void
{
  while(!t_str.empty()) {
    // Passing
    const auto last_ch{static_cast<unsigned char>(t_str.back())};
    if(std::isspace(last_ch)) {
      t_str.pop_back();
    } else {
      // Quit if the last character is not whitespace anymore.
      break;
    }
  }
}
} // namespace lib

#endif // ACRIS_LIB_STRING_UTIL_HPP
