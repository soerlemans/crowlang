#include "token.hpp"


using namespace token;
using namespace container;

Token::Token(const TokenType t_type, TextPosition t_tp)
  : m_type{t_type}, m_tp{std::move(t_tp)}
{}

Token::Token(const TokenType t_type, TokenValue t_tv, TextPosition t_tp)
  : m_type{t_type}, m_tv{std::move(t_tv)}, m_tp{std::move(t_tp)}
{}
