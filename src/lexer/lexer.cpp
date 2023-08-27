#include "lexer.hpp"

// STL Includes:
#include <cctype>
#include <ios>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <utility>

// Includes:
#include "../debug/log.hpp"
#include "../exception/syntax_error.hpp"


using namespace lexer;
using namespace token;
using namespace container;

// Error handling:
auto Lexer::syntax_error(std::string_view t_msg) const -> void
{
  // FIXME: The ^^^ does not properly align, columnno is possibly not
  // properly adjusted

  // Throws a SyntaxError with a message
  throw SyntaxError{std::string{t_msg}, m_tb->position()};
}

// Public constructors:
Lexer::Lexer(TextBufferPtr t_tb): m_tb{t_tb}
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
      DBG_LOG(INFO, "KEYWORD: ", t_identifier);
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
  // ss << m_tb->character();

  // while(is_valid_id(m_tb->peek()) && !m_tb->eol()) {
  //   ss << m_tb->forward();
  // }

  while(is_valid_id(m_tb->character()) && !m_tb->eol()) {
    ss << m_tb->forward();
  }

  // // We go back one since we add till we find a character that does not
  // // Match so we have to unget it
  m_tb->backward();

  // Verify if it is a keyword or not
  if(const auto opt{is_keyword(ss.str())}; opt) {
    token = create_token(opt.value());
  } else {
    DBG_LOG(INFO, "IDENTIFIER: ", ss.str());
    token = create_token(TokenType::IDENTIFIER, ss.str());
  }

  return token;
}

// Helper functions for literal_numeric
auto Lexer::is_hex_literal() -> bool
{
  bool is_hex{false};

  if(m_tb->forward() == '0' && m_tb->character() == 'x') {
    m_tb->forward(); // Discard 'x'

    is_hex = true;
  } else {
    // If we just have a zero we should go back to not discard the zero
    m_tb->backward();
  }

  return is_hex;
}

auto Lexer::handle_hex() -> Token
{
  std::stringstream ss;

  while(!m_tb->eol()) {
    const char character{m_tb->character()};

    if(std::isxdigit(character)) {
      ss << m_tb->forward();
    } else {
      m_tb->backward();
      break;
    }
  }

  DBG_LOG(INFO, "HEX: ", ss.str());
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
    m_tb->forward();

  while(!m_tb->eol()) {
    const char character{m_tb->character()};

    if(std::isdigit(character)) {
      ss << m_tb->forward();
    } else if(character == g_dot.m_identifier) {
      if(t_dot) {
        syntax_error("Cant have a second '.' in a float literal.");
      } else {
        t_dot = true;
      }
    } else {
      m_tb->backward();
      break;
    }
  }

  DBG_LOG(INFO, "FLOAT: ", ss.str());
  return create_token(TokenType::FLOAT, std::stod(ss.str()));
}

auto Lexer::handle_integer() -> Token
{
  using namespace reserved::symbols;

  std::stringstream ss;

  while(!m_tb->eol()) {
    const char character{m_tb->character()};

    if(std::isdigit(character)) {
      ss << m_tb->forward();
    } else if(character == g_dot.m_identifier) {
      ss << m_tb->character();

      // Handle float as a float
      return handle_float(ss.str(), true);
    } else {
      m_tb->backward();
      break;
    }
  }

  DBG_LOG(INFO, "INTEGER: ", ss.str());
  return create_token(TokenType::INTEGER, (int)std::stoi(ss.str()));
}

auto Lexer::literal_numeric() -> Token
{
  Token token;

  // Just forward to the apropiate numeric literal handle function
  if(is_hex_literal()) {
    token = handle_hex();
  } else {
    // handle_integer() may also forward to handle_float()
    token = handle_integer();
  }

  return token;
}

auto Lexer::literal_string() -> Token
{
  using namespace reserved::symbols::none;

  std::stringstream ss;

  // Discard starting " character
  m_tb->forward();

  bool quit{false};
  while(!quit && !m_tb->eol()) {
    const char character{m_tb->character()};

    switch(character) {
      case g_double_quote:
        quit = true;
        break;

      case g_backslash:
        ss << m_tb->forward();
        [[fallthrough]];

      default:
        ss << m_tb->forward();
        break;
    }
  }

  DBG_LOG(INFO, "STRING: ", '"', ss.str(), '"');
  return create_token(TokenType::STRING, ss.str());
}

auto Lexer::is_multi_symbol() -> TokenTypeOpt
{
  using namespace reserved::symbols;

  TokenTypeOpt opt;

  std::stringstream ss;
  const char character{m_tb->character()};

  ss << character;

  // TODO: We use two loops now, we can change this to only use one
  // Refactor someday
  for(const auto& multi : g_multi_symbols)
    if(character == multi.m_identifier.front()) {
      m_tb->forward();
      ss << m_tb->character();

      if(!m_tb->eol())
        for(const auto& multi : g_multi_symbols)
          if(ss.str() == multi.m_identifier) {
            DBG_LOG(INFO, "MULTI SYMBOL: ", ss.str());
            opt = multi.m_type;
            break;
          }

      // If the next character is not part if a multi symbol just undo the
      // forward
      if(!opt)
        m_tb->backward();

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
  const char character{m_tb->character()};

  for(const auto& single : g_single_symbols)
    if(character == single.m_identifier) {
      DBG_LOG(INFO, "SINGLE SYMBOL: ", character);
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
    ss << "Symbol encountered is not valid: " << m_tb->character() << '\n';
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

  for(; !m_tb->eof(); m_tb->next()) {
    for(; !m_tb->eol(); m_tb->forward()) {
      const char character{m_tb->character()};

      if(std::isspace(character)) {
        // Just ignore whitespace, but do not ignore newlines
        if(character == g_newline.m_identifier) {
          DBG_LOG(INFO, "NEWLINE");
          m_ts.push_back(create_token(TokenType::NEWLINE));
        }
      } else if(character == '#') {
        // '#' are used for comments.
        // If we just skip to the next line we ignore the \n at the end, so we
        // Must add a NEWLINE explicitly!
        // FIXME: Inserting NEWLINE is not needed?
        DBG_LOG(INFO, "INSERTING NEWLINE");
        m_ts.push_back(create_token(TokenType::NEWLINE));

        // Skip to next line
        break;
      } else if(std::isalpha(character)) {
        m_ts.push_back(identifier());
      } else if(std::isdigit(character)) {
        m_ts.push_back(literal_numeric());
      } else if(character == g_double_quote) {
        m_ts.push_back(literal_string());
      } else {
        m_ts.push_back(symbol());
      }
    }
  }

  return m_ts;
}
