#include "token.hpp"

// STL Includes:
#include <iostream>

// Local Includes:
#include "tokentype2str.hpp"

// Using statements:
using token::Token;

namespace token {
Token::Token(const TokenType t_type, TextPosition t_tp)
  : m_type{t_type}, m_tp{std::move(t_tp)}
{}

Token::Token(const TokenType t_type, TokenValue t_value, TextPosition t_tp)
  : m_type{t_type}, m_value{std::move(t_value)}, m_tp{std::move(t_tp)}
{}

auto Token::type() const -> TokenType
{
  return m_type;
}

auto Token::str() const -> std::string
{
  return get<std::string>();
}

auto Token::int_() const -> int
{
  return get<int>();
}

auto Token::double_() const -> double
{
  return get<double>();
}

auto Token::position() const -> const TextPosition&
{
  return m_tp;
}
} // namespace token

// Functions:
auto operator<<(std::ostream& t_os, const Token& t_token) -> std::ostream&
{
  t_os << t_token.type();

  return t_os;
}
