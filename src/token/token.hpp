#ifndef CROW_TOKEN_TOKEN_HPP
#define CROW_TOKEN_TOKEN_HPP

// STL Includes:
#include <string>
#include <variant>
#include <vector>

// Includes:
#include "../container/stream.hpp"
#include "../container/text_position.hpp"

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
  TokenValue m_tv;
  TextPosition m_tp;

  public:
  Token() = default;
  Token(const Token& t_token) = default;

  explicit Token(TokenType t_type, TextPosition t_tp);
  explicit Token(TokenType t_type, TokenValue t_tv, TextPosition t_tp);

	auto type() const -> TokenType;
	auto position() const -> TextPosition;

  virtual ~Token() = default;
};
} // namespace token

#endif // CROW_TOKEN_TOKEN_HPP
