#ifndef CROW_CROW_TOKEN_TOKEN_HPP
#define CROW_CROW_TOKEN_TOKEN_HPP

// STL Includes:
#include <iosfwd>
#include <string>
#include <variant>

// Absolute Includes:
#include "crow/container/text_position.hpp"

// Local Includes:
#include "token_type.hpp"

namespace token {
// Using Statements:
using container::TextPosition;

// Forward Declarations:
class Token;

// Aliases:
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

// Functions:
//! Used to convert @ref Token to a string representation.
auto token2str(const Token& t_token) -> std::string;
} // namespace token

// Functions:
auto operator<<(std::ostream& t_os, const token::Token& t_token)
  -> std::ostream&;

#endif // CROW_CROW_TOKEN_TOKEN_HPP
