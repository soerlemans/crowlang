#include "token.hpp"

// STL Includes:
#include <iostream>
#include <sstream>

// Local Includes:
#include "tokentype2str.hpp"

// Using statements:
using token::Token;

namespace token {
// Methods:
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

auto Token::int_() const -> i64
{
  return get<i64>();
}

auto Token::float_() const -> f64
{
  return get<f64>();
}

auto Token::char_() const -> char
{
  return get<char>();
}

auto Token::str() const -> std::string
{
  return get<std::string>();
}

auto Token::position() const -> const TextPosition&
{
  return m_tp;
}

// Functions:
auto token2str(const Token& t_token) -> std::string
{
  std::stringstream ss;

  // TODO: Also print the value in the following format:
  // (<type>, <value>)
  ss << t_token.type();

  return ss.str();
}
} // namespace token

// Functions:
auto operator<<(std::ostream& t_os, const Token& t_token) -> std::ostream&
{
  t_os << token::token2str(t_token);

  return t_os;
}
