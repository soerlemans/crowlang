#include "tokenstream.hpp"

#include <sstream>

// Private Functions:
namespace {
/*!
 * Convert a string to a raw string.
 */
std::string escape_str(const std::string_view& t_str)
{
  std::stringstream ss;
  for(const auto ch : t_str) {
    switch(ch) {
      case '\\':
        ss << "\\\\"; // Escape backslashes.
        break;

      case '"':
        ss << "\\\""; // Escape double quotes.
        break;

      case '\n':
        ss << "\\n"; // Escape newline.
	break;

      default:
        ss << ch; // Append normal characters.
        break;
    }
  }

  return ss.str();
}
} // namespace

auto operator<<(std::ostream& t_os, const token::TokenStream& t_ts)
  -> std::ostream&
{
  t_os << '[';

  for(const auto& tok : t_ts) {
    const auto str{token::token2str(tok)};

    t_os << escape_str(str) << ", ";
  }

  t_os << ']';

  return t_os;
}
