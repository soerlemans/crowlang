#ifndef CROW_CROW_TOKEN_TOKENTYPE2STR_HPP
#define CROW_CROW_TOKEN_TOKENTYPE2STR_HPP

// STL Includes:
#include <ostream>
#include <string>

// Local Includes:
#include "token_type.hpp"

namespace token {
auto tokentype2str(TokenType t_type) -> std::string;
} // namespace token

auto operator<<(std::ostream& t_os,
                const token::TokenType t_type) -> std::ostream&;

#endif // CROW_CROW_TOKEN_TOKENTYPE2STR_HPP
