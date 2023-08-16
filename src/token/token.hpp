#ifndef NEWLANG_TOKEN_TOKEN_HPP
#define NEWLANG_TOKEN_TOKEN_HPP

// STL Includes:
#include <string>
#include <variant>
#include <vector>

// Includes:
#include "../container/stream.hpp"

// Local Includes:
#include "token_type.hpp"


namespace token {
// Using declarations:
using namespace container;

// Forward Declarations:
class Token;

// Aliases:
using TokenStream = Stream<std::vector<Token>>;
using TokenValue = std::variant<int, double, std::string>;

// Classes:
class Token {
  private:
  TokenType m_type;
  TokenValue m_value;

  public:
  Token(TokenType t_type);

  virtual ~Token() = default;
};
} // namespace token

#endif // NEWLANG_TOKEN_TOKEN_HPP
