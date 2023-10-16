#include "token.hpp"


using namespace token;
using namespace container;

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

auto Token::position() const -> TextPosition
{
  return m_tp;
}
