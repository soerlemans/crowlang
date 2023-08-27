#ifndef CROW_PARSER_PARSER_HPP
#define CROW_PARSER_PARSER_HPP

// STL Includes:
#include <functional>

// Includes:
#include "../ast/node.hpp"
#include "../debug/trace.hpp"
#include "../lexer/lexer.hpp"


namespace parser {
// Aliases:
//! Used for functions that need to have different parsing rules dependent on
//! Context
// using ParserFunc = std::function<node::NodePtr()>;

// Classes:
/*! Abstract parser class provides utilities that a parser would need to
 * implement
 */
class Parser {
  private:
  token::TokenStream m_tokenstream;

  protected:
  DBG_TRACE_INIT()

  // m_tokenstream helper methods:
  auto syntax_error(std::string_view t_msg) const -> void;
  auto eos_error(std::string_view t_msg) const -> void;

  auto eos() const -> bool;

  auto check(token::TokenType t_tokentype) -> bool;
  auto next() -> token::Token&;
  auto next_if(token::TokenType t_tokentype) -> bool;
  auto expect(token::TokenType t_tokentype, std::string_view t_msg)
    -> token::Token&;
  auto prev() -> token::Token&;
  auto get_token() const -> token::Token;

  public:
  Parser(token::TokenStream&& t_tokenstream);

  virtual auto parse() -> ast::NodePtr = 0;

  virtual ~Parser() = default;
};
} // namespace parser

#endif // CROW_PARSER_PARSER_HPP
