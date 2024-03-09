#include "tokentype2str.hpp"

// STL Includes:
#include <optional>
#include <sstream>
#include <stdexcept>

// Local Includes
#include "reserved/reserved.hpp"

// Macros:
#define OPT_FORWARD(t_opt)           \
  do {                               \
    if(const auto opt{t_opt}; opt) { \
      return opt.value();            \
    }                                \
  } while(false)

#define CASE_STR(t_type)  \
  case TokenType::t_type: \
    return #t_type;


// Using statements:
using namespace token;

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
    CASE_STR(IDENTIFIER)

    // Literals:
    CASE_STR(INTEGER)
    CASE_STR(FLOAT)
    CASE_STR(STRING)

    // Braces:
    CASE_STR(PAREN_OPEN)
    CASE_STR(PAREN_CLOSE)
    CASE_STR(ACCOLADE_OPEN)
    CASE_STR(ACCOLADE_CLOSE)
    CASE_STR(BRACE_OPEN)
    CASE_STR(BRACE_CLOSE)

    // Miscellaneous:
    CASE_STR(NEWLINE)

    default:
      break;
  }

  throw std::invalid_argument{
    "TokenType can not be converteted to std::string_view"};
}
} // namespace token

auto operator<<(std::ostream& t_os, const TokenType t_type) -> std::ostream&
{
  t_os << token::tokentype2str(t_type);

  return t_os;
}
