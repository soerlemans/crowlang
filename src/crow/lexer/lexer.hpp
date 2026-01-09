#ifndef CROW_CROW_LEXER_LEXER_HPP
#define CROW_CROW_LEXER_LEXER_HPP

// STL Includes:
#include <string>
#include <string_view>
#include <tuple>

// Absolute Includes:
#include "crow/container/text_stream.hpp"
#include "crow/token/reserved/reserved.hpp"
#include "crow/token/token_stream.hpp"

namespace lexer {
// Using Statements:
using container::TextPosition;
using container::TextStreamPtr;
using token::Token;
using token::TokenStream;
using token::TokenTypeOpt;

// Classes:
class Lexer {
  private:
  TextStreamPtr m_text;
  TokenStream m_ts;

  protected:
  auto text_position() const -> TextPosition;

  auto throw_syntax_error(std::string_view t_msg) const -> void;

  public:
  explicit Lexer(TextStreamPtr t_text);

  // Misc:
  auto newline() -> Token;

  // Comment:
  auto handle_line_comment() -> Token;
  auto handle_block_comment() -> Token;

  auto is_comment() -> bool;
  auto comment() -> Token;

  // Name:
  static auto is_keyword(std::string_view t_identifier) -> TokenTypeOpt;
  auto identifier() -> Token;

  // Integer literal lexing:
  auto is_hex_literal() -> bool;
  auto handle_hex() -> Token;
  auto handle_float(std::string_view t_str) -> Token;
  auto handle_integer() -> Token;

  // Literal lexing:
  auto literal_numeric() -> Token;
  auto literal_string() -> Token;

  // Symbol lexing:
  auto is_multi_symbol() -> TokenTypeOpt;
  auto is_single_symbol() -> TokenTypeOpt;
  auto symbol() -> Token;

  auto tokenize() -> TokenStream;

  virtual ~Lexer() = default;
};
} // namespace lexer

#endif // CROW_CROW_LEXER_LEXER_HPP
