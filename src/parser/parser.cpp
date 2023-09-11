#include "parser.hpp"

// Includes:
#include "../exception/syntax_error.hpp"
#include "../token/tokentype2str.hpp"


// Using statements:
using namespace parser;
using namespace token;

// Methods:
Parser::Parser(TokenStream&& t_tokenstream)
  : m_tokenstream{std::forward<TokenStream>(t_tokenstream)}
{}

auto Parser::syntax_error(std::string_view t_msg) const -> void
{
  const auto token{get_token()};

  throw SyntaxError{std::string{t_msg}, token.position()};
}

// FIXME: This function should be replaced with the printing of a stacktrace
auto Parser::eos_error(const std::string_view t_msg) const -> void
{
  if(m_tokenstream.eos()) {
    // TODO: Make a function for this
    std::stringstream ss;
    ss << "EOS reached!\n";
    ss << " - ";
    ss << t_msg;

    throw std::runtime_error{ss.str()};
  }
}

auto Parser::eos() const -> bool
{
  return m_tokenstream.eos();
}

auto Parser::check(const TokenType t_type) -> bool
{
  eos_error("Tried to check for token at EOS!");

  const auto token{m_tokenstream.current()};

  return token.type() == t_type;
}

auto Parser::next() -> Token&
{
  eos_error("Tried to move to next Token at EOS!");

  return m_tokenstream.next();
}

auto Parser::next_if(const TokenType t_type) -> bool
{
  eos_error(
    "Tried to move to next if Token is equal to expected token at EOS!");

  // Only go to next token if we find the token we expect
  const auto advance{check(t_type)};
  if(advance) {
    next();
  }

  return advance;
}

auto Parser::expect(const TokenType t_type) -> Token&
{
  if(!check(t_type)) {
    std::stringstream ss;
    ss << "Expected -> ";
    ss << std::quoted(tokentype2str(t_type), '\'');

    syntax_error(ss.str());
  }

  auto& token{get_token()};

  next();

  return token;
}

auto Parser::prev() -> Token&
{
  return m_tokenstream.prev();
}

auto Parser::get_token() const -> Token&
{
  eos_error("Tried to return get token at EOS!");

  return m_tokenstream.current();
}

//! This method is used to verify if a certain token is located after newlines
auto Parser::after_newlines(const token::TokenType t_type) -> bool
{
  DBG_TRACE_FN(VERBOSE);

  bool found{false};

  for(auto iter{m_tokenstream.iter()}; iter != m_tokenstream.end(); iter++) {
    if(iter->type() != TokenType::NEWLINE) {
      if(iter->type() == t_type) {
        found = true;

        DBG_TRACE_PRINT(VERBOSE,
                        "Found: ", std::quoted(tokentype2str(t_type), '\''));

        // Update iterator
        m_tokenstream.set(iter);
      }

      break;
    }
  }

  return found;
}
