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
using TokenOpt = std::optional<Token>;
using TokenStream = Stream<std::vector<Token>>;
using TokenValue = std::variant<int, double, std::string>;

// Classes:
class Token {
  private:
  TokenType m_type;
  TokenValue m_value;
  TextPosition m_tp;

  public:
  Token() = default;
  Token(const Token& t_token) = default;

  explicit Token(TokenType t_type, TextPosition t_tp);
  explicit Token(TokenType t_type, TokenValue t_value, TextPosition t_tp);

  auto type() const -> TokenType;

  template<typename T>
  auto get() const -> T
  {
    return std::get<T>(m_value);
  }

  auto str() const -> std::string;
  auto int_() const -> int;
  auto double_() const -> double;

  auto position() const -> const TextPosition&;

  virtual ~Token() = default;
};
} // namespace token

#endif // CROW_TOKEN_TOKEN_HPP
