#ifndef NEWLANG_LEXER_LEXER_HPP
#define NEWLANG_LEXER_LEXER_HPP

// STL Includes:
#include <string>
#include <string_view>
#include <tuple>

// Includes:
#include "../container/text_buffer.hpp"
#include "../token/reserved/reserved.hpp"
#include "../token/token.hpp"


namespace lexer {
// Using declarations:
using namespace container;

// Classes:
class Lexer {
  private:
  TextBufferPtr m_tb;
  token::TokenStream m_ts;

  // Token stream handling:
  //! Create a token with a TextPosition
  template<typename... Args>
  auto create_token(Args&&... t_args) -> token::Token
  {
    return token::Token{std::forward<Args>(t_args)..., m_tb->position()};
  }

  // Error handling:
  auto syntax_error(std::string_view t_msg) const -> void;

  public:
  Lexer(TextBufferPtr t_fb);

  // Name lexing:
  static auto is_keyword(std::string_view t_identifier) -> token::TokenTypeOpt;
  auto identifier() -> token::Token;

  // Integer literal lexing:
  auto is_hex_literal() -> bool;
  auto handle_hex() -> token::Token;
  auto handle_float(std::string_view t_str = "", bool t_dot = false)
    -> token::Token;
  auto handle_integer() -> token::Token;

  // Literal lexing:
  auto literal_numeric() -> token::Token;
  auto literal_string() -> token::Token;

  // Symbol lexing:
  auto is_multi_symbol() -> token::TokenTypeOpt;
  auto is_single_symbol() -> token::TokenTypeOpt;
  auto symbol() -> token::Token;

  auto tokenize() -> token::TokenStream;

  virtual ~Lexer() = default;
};
} // namespace lexer

#endif // NEWLANG_LEXER_LEXER_HPP
