#ifndef FORMAT_HPP
#define FORMAT_HPP

// STL Include:
#include <format>

namespace lib::stdfmt {
// TODO: Still figure out if this is the way to go.
// Define a custom formatter for std::string.
template<>
struct std::formatter<std::string> : std::formatter<std::string_view> {
  template<typename FormatContext>
  auto format(const std::string& str, FormatContext& ctx)
  {
    auto&& spec = ctx.spec();

    if(spec.has_flag('Q')) {
      return std::formatter<std::string_view>::format('"' + str + '"', ctx);
    }

    if(spec.has_flag('q')) {
      return std::formatter<std::string_view>::format('\'' + str + '\'', ctx);
    }

    // Otherwise, format the string as is
    return std::formatter<std::string_view>::format(str, ctx);
  }
};
} // namespace lib

#endif // FORMAT_HPP
