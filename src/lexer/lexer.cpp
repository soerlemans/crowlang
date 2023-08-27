#include "lexer.hpp"

// STL Includes:
#include <cctype>
#include <ios>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <utility>

// Includes:
#include "../debug/log.hpp"
#include "../exception/syntax_error.hpp"


// Macros:
#define LEX_LOG(t_str, t_quoted) \
	DBG_LOG(INFO, t_str, std::quoted(std::string{t_quoted}))

// Using statements:
using namespace lexer;
using namespace token;
using namespace container;

// Error handling:
auto Lexer::syntax_error(std::string_view t_msg) const -> void
{
  // FIXME: The ^^^ does not properly align, columnno is possibly not
  // properly adjusted

  // Throws a SyntaxError with a message
  throw SyntaxError{std::string{t_msg}, m_text->position()};
}

// Public constructors:
Lexer::Lexer(TextStreamPtr t_text): m_text{t_text}
{}

// Public methods:
auto Lexer::is_keyword(std::string_view t_identifier) -> TokenTypeOpt
{
  using namespace reserved::keywords;

  TokenTypeOpt opt;

  // TODO: Clean this up we could use a loop with an std::pair for the tokentype
  // Having a centralized location for
  for(const auto& keyword : g_keywords)
    if(t_identifier == keyword.m_identifier) {
      LEX_LOG("KEYWORD: ", t_identifier);
      opt = keyword.m_type;
      break;
    }

  return opt;
}

auto Lexer::identifier() -> Token
{
  using namespace reserved::symbols;

  Token token;
  std::stringstream ss;

  auto is_valid_id{[&](const char t_char) -> bool {
    return std::isalnum(t_char) || t_char == '_';
  }};

  // If Peek is implemented this works
  // ss << m_text->character();

  // while(is_valid_id(m_text->peek()) && !m_text->eos()) {
  //   ss << m_text->next();
  // }

  while(is_valid_id(m_text->character()) && !m_text->eos()) {
    ss << m_text->next();
  }

  // // We go back one since we add till we find a character that does not
  // // Match so we have to unget it
  m_text->prev();

  // Verify if it is a keyword or not
  if(const auto opt{is_keyword(ss.str())}; opt) {
    token = create_token(opt.value());
  } else {
    LEX_LOG("IDENTIFIER: ", ss.str());
    token = create_token(TokenType::IDENTIFIER, ss.str());
  }

  return token;
}

// Helper functions for literal_numeric
auto Lexer::is_hex_literal() -> bool
{
  bool is_hex{false};

  if(m_text->next() == '0' && m_text->character() == 'x') {
    m_text->next(); // Discard 'x'

    is_hex = true;
  } else {
    // If we just have a zero we should go back to not discard the zero
    m_text->prev();
  }

  return is_hex;
}

auto Lexer::handle_hex() -> Token
{
  std::stringstream ss;

  while(!m_text->eos()) {
    const char character{m_text->character()};

    if(std::isxdigit(character)) {
      ss << m_text->next();
    } else {
      m_text->prev();
      break;
    }
  }

  LEX_LOG("HEX: ", ss.str());
  const int number{(int)std::stoul(ss.str(), nullptr, 16)};

  return create_token(TokenType::INTEGER, number);
}

// t_str and t_dot have default arguments
// t_str contains is for if you already have part of a string to continue on
// t_dot indicates if there is already a dot in the string
auto Lexer::handle_float(std::string_view t_str, bool t_dot) -> Token
{
  using namespace reserved::symbols;

  std::stringstream ss;

  ss << t_str;

  if(t_dot)
    m_text->next();

  while(!m_text->eos()) {
    const char character{m_text->character()};

    if(std::isdigit(character)) {
      ss << m_text->next();
    } else if(character == g_dot.m_identifier) {
      if(t_dot) {
        syntax_error("Cant have a second '.' in a float literal.");
      } else {
        t_dot = true;
      }
    } else {
      m_text->prev();
      break;
    }
  }

  LEX_LOG("FLOAT: ", ss.str());
  return create_token(TokenType::FLOAT, std::stod(ss.str()));
}

auto Lexer::handle_integer() -> Token
{
  using namespace reserved::symbols;

  std::stringstream ss;

  while(!m_text->eos()) {
    const char character{m_text->character()};

    if(std::isdigit(character)) {
      ss << m_text->next();
    } else if(character == g_dot.m_identifier) {
      ss << m_text->character();

      // Handle float as a float
      return handle_float(ss.str(), true);
    } else {
      m_text->prev();
      break;
    }
  }

  LEX_LOG("INTEGER: ", ss.str());
  return create_token(TokenType::INTEGER, (int)std::stoi(ss.str()));
}

auto Lexer::literal_numeric() -> Token
{
  Token token;

  // Just next to the apropiate numeric literal handle function
  if(is_hex_literal()) {
    token = handle_hex();
  } else {
    // handle_integer() may also next to handle_float()
    token = handle_integer();
  }

  return token;
}

auto Lexer::literal_string() -> Token
{
  using namespace reserved::symbols::none;

  std::stringstream ss;

  // Discard starting " character
  m_text->next();

  bool quit{false};
  while(!quit && !m_text->eos()) {
    const char character{m_text->character()};

    switch(character) {
      case g_double_quote:
        quit = true;
        break;

      case g_backslash:
        ss << m_text->next();
        [[fallthrough]];

      default:
        ss << m_text->next();
        break;
    }
  }

  LEX_LOG("STRING: ", ss.str());
  return create_token(TokenType::STRING, ss.str());
}

auto Lexer::is_multi_symbol() -> TokenTypeOpt
{
  using namespace reserved::symbols;

  TokenTypeOpt opt;

  std::stringstream ss;
  const char character{m_text->character()};

  ss << character;

  // TODO: We use two loops now, we can change this to only use one
  // Refactor someday
  for(const auto& multi : g_multi_symbols)
    if(character == multi.m_identifier.front()) {
      m_text->next();
      ss << m_text->character();

      if(!m_text->eos())
        for(const auto& multi : g_multi_symbols)
          if(ss.str() == multi.m_identifier) {
            LEX_LOG("MULTI SYMBOL: ", ss.str());
            opt = multi.m_type;
            break;
          }

      // If the next character is not part if a multi symbol just undo the
      // next
      if(!opt)
        m_text->prev();

      // We compare against all reserverd multi symbols in the second loop
      // So there is no need to iterate againt after we found our first match
      break;
    }

  return opt;
}

auto Lexer::is_single_symbol() -> TokenTypeOpt
{
  using namespace reserved::symbols;

  TokenTypeOpt opt;
  const char character{m_text->character()};

  for(const auto& single : g_single_symbols)
    if(character == single.m_identifier) {
      LEX_LOG("SINGLE SYMBOL: ", character);
      opt = single.m_type;
      break;
    }

  return opt;
}

auto Lexer::symbol() -> Token
{
  TokenTypeOpt opt;

  // First check for multi symbol
  opt = is_multi_symbol();

  // Then check for single symbol
  if(!opt)
    opt = is_single_symbol();

  // Throw if it is neither
  if(!opt) {
    std::stringstream ss;
    ss << "Symbol encountered is not valid: " << m_text->character() << '\n';
    syntax_error(ss.str());
  }

  // Add the symbol if we recognize it
  return create_token(opt.value());
}

// TODO: refactor this
auto Lexer::tokenize() -> TokenStream
{
  using namespace reserved::symbols;
  using namespace reserved::symbols::none;

  while(!m_text->eos()) {
    const auto ch{m_text->character()};

    if(std::isspace(ch)) {
      // Just ignore whitespace, but do not ignore newlines
      if(ch == g_newline.m_identifier) {
        DBG_LOG(INFO, "NEWLINE");
        m_ts.push_back(create_token(TokenType::NEWLINE));
      }
    } else if(ch == '#') {
      // '#' are used for comments.
      // If we just skip to the next line we ignore the \n at the end, so we
      // Must add a NEWLINE explicitly!
      // FIXME: Inserting NEWLINE is not needed?
      DBG_LOG(INFO, "INSERTING NEWLINE");
      m_ts.push_back(create_token(TokenType::NEWLINE));

      // Skip to next line
      m_text->next_line();
      continue;
    } else if(std::isalpha(ch)) {
      m_ts.push_back(identifier());
    } else if(std::isdigit(ch)) {
      m_ts.push_back(literal_numeric());
    } else if(ch == g_double_quote) {
      m_ts.push_back(literal_string());
    } else {
      m_ts.push_back(symbol());
    }

    m_text->next();
  }

  return m_ts;
}
