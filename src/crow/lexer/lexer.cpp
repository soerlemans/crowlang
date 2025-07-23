#include "lexer.hpp"

// STL Includes:
#include <cctype>
#include <iomanip>
#include <ios>
#include <sstream>
#include <stdexcept>
#include <utility>

// Absolute Includes:
#include "crow/debug/log.hpp"
#include "crow/diagnostic/syntax_error.hpp"

// TODO: Fix use of cctype functions in the lexer.
// Currently we use the cctype functions.
// Which are local dependent and also have undefined behavior.
// For signed char, which is the default type of std::string.
// So we need to create safe wrappers that maybe throw on negative input.
// Oneday we should implement unicode, support via std::u8string.

// Macros:
#define LOG_TOKEN(t_msg, t_str) DBG_INFO(t_msg, std::quoted(std::string{t_str}))

namespace lexer {
// Using Statements:
using token::TokenType;

// Protected Methods:
auto Lexer::text_position() const -> TextPosition
{
  return m_text->position();
}

auto Lexer::throw_syntax_error(const std::string_view t_msg) const -> void
{
  using diagnostic::SyntaxError;

  throw SyntaxError{std::string{t_msg}, text_position()};
}

// Public methods:
Lexer::Lexer(TextStreamPtr t_text): m_text{t_text}
{}

auto Lexer::newline() -> Token
{
  const auto position{text_position()};

  // Generally whitespace is ignored.
  // Newlines are used for statement/semicolon interference.
  // So they are a part of the grammar.
  DBG_INFO("NEWLINE");
  return Token{TokenType::NEWLINE, position};
}

auto Lexer::handle_line_comment() -> Token
{
  using namespace token::reserved::symbols::none;

  std::stringstream ss;

  const auto position{text_position()};
  m_text->next(); // Discard '/'.
  m_text->next(); // Discard '/'.

  while(!m_text->eos()) {
    const auto ch{m_text->character()};

    // Line comments stop on newlines.
    if(ch == g_newline) {
      break;
    }

    ss << ch;

    m_text->next();
  }

  LOG_TOKEN("LINE_COMMENT: ", ss.str());
  return Token{TokenType::LINE_COMMENT, ss.str(), position};
}

auto Lexer::handle_block_comment() -> Token
{
  using namespace token::reserved::symbols::none;

  std::stringstream ss;

  const auto position{text_position()};
  m_text->next(); // Discard '/'.
  m_text->next(); // Discard '*'.

  while(!m_text->eos()) {
    const auto ch{m_text->character()};

    // We ignore Asterisks.
    if(ch == g_asterisk) {
      // block comments stop on */.
      if(const auto opt{m_text->peek()}; opt) {
        if(opt.value() == g_slash) {
          m_text->next();
          break;
        }
      }
    } else {
      ss << ch;
    }

    m_text->next();
  }

  LOG_TOKEN("BLOCK_COMMENT:\n", ss.str());
  return Token{TokenType::BLOCK_COMMENT, ss.str(), position};
}

/*!
 * Determine if we are at the start of a comment.
 */
auto Lexer::is_comment() -> bool
{
  using namespace token::reserved::symbols::none;

  auto ret{false};

  const auto ch{m_text->character()};
  if(const auto opt{m_text->peek()}; opt && ch == g_slash) {
    const auto peek_ch{opt.value()};
    if(peek_ch == g_slash || peek_ch == g_asterisk) {
      ret = true;
    }
  }

  return ret;
}

auto Lexer::comment() -> Token
{
  using namespace token::reserved::symbols::none;

  Token token;
  std::stringstream ss;

  // Check the second character after the '/' to determine.
  // If this is a line comment or block comment.
  if(const auto opt{m_text->peek()}; opt) {
    const auto peek_ch{opt.value()};

    // Is a comment:
    if(peek_ch == g_slash) {
      token = handle_line_comment();

      // Is a comment block:
    } else if(peek_ch == g_asterisk) {
      token = handle_block_comment();
    }
  }

  return token;
}

auto Lexer::is_keyword(const std::string_view t_identifier) -> TokenTypeOpt
{
  using namespace token::reserved::keywords;

  TokenTypeOpt opt;

  // If the keyword was found return its @ref TokenType.
  if(const auto iter{g_keywords.find(t_identifier)}; iter != g_keywords.end()) {
    LOG_TOKEN("KEYWORD: ", iter->first);
    opt = iter->second;
  }

  return opt;
}

auto Lexer::identifier() -> Token
{
  using namespace token::reserved::symbols;

  Token token;
  auto position{text_position()};
  std::stringstream ss;

  auto is_valid_id{[&](const char t_char) -> bool {
    return std::isalnum(t_char) || t_char == '_';
  }};

  // Extract identifier:
  const auto ch{m_text->character()};
  if(std::isalpha(ch)) {
    ss << ch;
    while(!m_text->eos()) {
      const auto opt{m_text->peek()};

      if(opt && is_valid_id(opt.value())) {
        m_text->next();
        ss << m_text->character();
      } else {
        break;
      }
    }
  }

  // Verify if it is a keyword or not
  if(const auto opt{is_keyword(ss.str())}; opt) {
    token = Token{opt.value(), position};
  } else {
    LOG_TOKEN("IDENTIFIER: ", ss.str());
    token = Token{TokenType::IDENTIFIER, ss.str(), position};
  }

  return token;
}

// Helper functions for literal_numeric
auto Lexer::is_hex_literal() -> bool
{
  bool is_hex{false};

  if(m_text->character() == '0' && m_text->peek() == 'x') {
    m_text->next(); // Discard '0'.
    m_text->next(); // Discard 'x'.

    is_hex = true;
  }

  return is_hex;
}

auto Lexer::handle_hex() -> Token
{
  auto position{text_position()};

  std::stringstream ss;

  // Extract hex
  const auto ch{m_text->character()};
  if(std::isxdigit(ch)) {
    ss << ch;

    while(!m_text->eos()) {
      if(const auto opt{m_text->peek()}; opt) {
        if(std::isxdigit(opt.value())) {
          m_text->next();
          ss << m_text->character();
        } else {
          break;
        }
      }
    }
  }

  LOG_TOKEN("HEX: ", ss.str());
  const int number{(int)std::stoul(ss.str(), nullptr, 16)};

  return Token(TokenType::INTEGER, number, position);
}

// t_str and t_dot have default arguments
// t_str contains is for if you already have part of a string to continue on
// t_dot indicates if there is already a dot in the string
auto Lexer::handle_float(const std::string_view t_str) -> Token
{
  using namespace token::reserved::symbols;

  auto position{text_position()};

  std::stringstream ss;
  ss << t_str;

  while(!m_text->eos()) {
    const auto ch{m_text->peek()};
    if(ch) {
      if(std::isdigit(ch.value())) {
        m_text->next();
        ss << m_text->character();
      } else if(ch.value() == g_dot.m_identifier) {
        throw_syntax_error("Cant have a second '.' in a float literal.");
      } else {
        break;
      }
    }
  }

  LOG_TOKEN("FLOAT: ", ss.str());
  const f64 number{std::stod(ss.str())};

  return Token{TokenType::FLOAT, number, position};
}

auto Lexer::handle_integer() -> Token
{
  using namespace token::reserved::symbols;

  auto position{text_position()};

  std::stringstream ss;

  // Extract integer.
  if(std::isdigit(m_text->character())) {
    ss << m_text->character();
    while(!m_text->eos()) {
      if(const auto ch{m_text->peek()}; ch) {
        if(std::isdigit(ch.value())) {
          m_text->next();
          ss << m_text->character();
        } else if(ch.value() == g_dot.m_identifier) {
          m_text->next();
          ss << m_text->character();

          return handle_float(ss.str());
        } else {
          break;
        }
      }
    }
  }

  LOG_TOKEN("INTEGER: ", ss.str());
  const int number{std::stoi(ss.str())};

  return Token{TokenType::INTEGER, number, position};
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
  using namespace token::reserved::symbols::none;

  const auto position{text_position()};
  std::stringstream ss;

  bool quit{false};
  while(!quit && !m_text->eos()) {
    if(const auto ch{m_text->peek()}; ch) {
      m_text->next();
      switch(ch.value()) {
        case g_double_quote:
          quit = true;
          break;

        case g_backslash:
          ss << m_text->character();
          m_text->next();
          [[fallthrough]];

        default:
          ss << m_text->character();
          break;
      }
    }
  }

  LOG_TOKEN("STRING: ", ss.str());
  return Token{TokenType::STRING, ss.str(), position};
}

auto Lexer::is_multi_symbol() -> TokenTypeOpt
{
  using namespace token::reserved::symbols;

  TokenTypeOpt opt;

  std::stringstream ss;
  const char character{m_text->character()};

  ss << character;

  if(const auto ch{m_text->peek()}; ch) {
    ss << ch.value();

    if(const auto iter{g_multi_symbols.find(ss.str())};
       iter != g_multi_symbols.end()) {
      LOG_TOKEN("MULTI SYMBOL: ", iter->first);
      opt = iter->second;
      m_text->next();
    }
  }

  return opt;
}

auto Lexer::is_single_symbol() -> TokenTypeOpt
{
  using namespace token::reserved::symbols;

  TokenTypeOpt opt;
  const auto ch{m_text->character()};

  if(const auto iter{g_single_symbols.find(ch)};
     iter != g_single_symbols.end()) {
    LOG_TOKEN("SINGLE SYMBOL: ", iter->first);
    opt = iter->second;
  }

  return opt;
}

auto Lexer::symbol() -> Token
{
  const auto position{text_position()};
  TokenTypeOpt opt;

  // First check for multi symbol
  opt = is_multi_symbol();

  // Then check for single symbol
  if(!opt) {
    opt = is_single_symbol();
  }

  // Throw if it is neither
  if(!opt) {
    std::stringstream ss;
    ss << "Symbol encountered is not valid: " << m_text->character() << '\n';
    throw_syntax_error(ss.str());
  }

  // Add the symbol if we recognize it
  return Token{opt.value(), position};
}

// TODO: refactor this
auto Lexer::tokenize() -> TokenStream
{
  using namespace token::reserved::symbols;

  while(!m_text->eos()) {
    const auto ch{m_text->character()};

    // Lexing loop:
    if(std::isspace(ch)) {
      // Ignore everything except newlines.
      if(ch == g_newline.m_identifier) {
        m_ts.push_back(newline());
      }
    } else if(is_comment()) {
      // TODO: Currently comments are not part of the grammar.
      // Meaning we have no way to properly translate them to source yet.
      // If we want the generated C++ code to have comments.
      // We need to find a way to translate it to the source.
      // This is especially the case for documentation comments (start with !).
      // For now we discard comments.
      comment();
      // m_ts.push_back(comment());

      // '//' and '/*' are used for comments.
      // If we just skip to the next line we ignore the \n at the end.
      // So we must add a NEWLINE explicitly!
      DBG_INFO("INSERTING NEWLINE");
      m_ts.emplace_back(TokenType::NEWLINE, text_position());
    } else if(std::isalpha(ch)) {
      // TODO: Add a check for raw string literals like r"" (use peek).
      m_ts.push_back(identifier());
    } else if(std::isdigit(ch)) {
      m_ts.push_back(literal_numeric());
    } else if(ch == none::g_double_quote) {
      m_ts.push_back(literal_string());
    } else {
      m_ts.push_back(symbol());
    }

    m_text->next();
  }

  return m_ts;
}
} // namespace lexer
