#ifndef TOKENTYPE2STR_HPP
#define TOKENTYPE2STR_HPP

// STL Includes:
#include <string>

// Local Includes:
#include "token_type.hpp"


namespace token {
auto tokentype2str(token::TokenType t_type) -> std::string;
} // namespace token

#endif // TOKENTYPE2STR_HPP
