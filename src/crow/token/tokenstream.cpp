#include "tokenstream.hpp"

#include <sstream>

// Private Functions:
namespace {
/*!
 * Escape all special characters and backslashes.
 *
 * @note FIXME: Place somewhere more appropiate, likely in src/lib.
 * This is a utility function so it should probably go there.
 */
std::string escape_str(const std::string_view& t_str)
{
  std::stringstream ss;
  for(const auto ch : t_str) {
    switch(ch) {
      case '\t':
        ss << "\\t"; // Escape tab.
        break;

      case '\n':
        ss << "\\n"; // Escape newline.
        break;

      case '\v':
        ss << "\\v"; // Escape vertical tab.
        break;

      case '\r':
        ss << "\\r"; // Escape carriage return.
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
