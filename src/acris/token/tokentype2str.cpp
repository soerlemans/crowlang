#include "tokentype2str.hpp"

// STL Includes:
#include <optional>
#include <sstream>
#include <stdexcept>

// Absolute Includes:
#include "acris/debug/log.hpp"

// Local Includes:
#include "reserved/reserved.hpp"

// Macros:
#define OPT_FORWARD(t_opt)           \
  do {                               \
    if(const auto opt{t_opt}; opt) { \
      return opt.value();            \
    }                                \
  } while(false)

#define MATCH_STR(t_type) \
  case TokenType::t_type: \
    return #t_type;

// Using statements:
using token::TokenType;

namespace {
// Aliases:
using StrOpt = std::optional<std::string>;

// Functions:
// FIXME: This reverse lookup is O(n), can be more efficient with boost bimap.
template<typename T>
auto reverse_lookup(const TokenType t_type, const T& t_map) -> StrOpt
{
  StrOpt opt;
  std::stringstream ss;

  for(const auto& pair : t_map) {
    if(pair.second == t_type) {
      ss << pair.first;
      opt = ss.str();
      break;
    }
  }

  return opt;
}
} // namespace

namespace token {
// Functions:
auto tokentype2str(const token::TokenType t_type) -> std::string
{
  using namespace reserved::keywords;
  using namespace reserved::symbols;

  OPT_FORWARD(reverse_lookup(t_type, g_keywords));
  OPT_FORWARD(reverse_lookup(t_type, g_single_symbols));
  OPT_FORWARD(reverse_lookup(t_type, g_multi_symbols));

  // Miscellenous:
  switch(t_type) {
    MATCH_STR(IDENTIFIER)

    // Literals:
    MATCH_STR(INTEGER_LITERAL)
    MATCH_STR(FLOAT_LITERAL)
    MATCH_STR(CHAR_LITERAL)
    MATCH_STR(STRING_LITERAL)

    // Braces:
    MATCH_STR(PAREN_OPEN)
    MATCH_STR(PAREN_CLOSE)
    MATCH_STR(ACCOLADE_OPEN)
    MATCH_STR(ACCOLADE_CLOSE)
    MATCH_STR(BRACKET_OPEN)
    MATCH_STR(BRACKET_CLOSE)

    // Comments:
    MATCH_STR(LINE_COMMENT)
    MATCH_STR(BLOCK_COMMENT)

    // Miscellaneous:
    MATCH_STR(NEWLINE)

    default:
      const std::string_view str{
        "TokenType could not be converteted to std::string_view."};

      DBG_ERROR(str);
      throw std::invalid_argument{str.data()};
      break;
  }

  return {};
}
} // namespace token

auto operator<<(std::ostream& t_os, const TokenType t_type) -> std::ostream&
{
  t_os << token::tokentype2str(t_type);

  return t_os;
}
