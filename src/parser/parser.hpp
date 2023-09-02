#ifndef CROW_PARSER_PARSER_HPP
#define CROW_PARSER_PARSER_HPP

// STL Includes:
#include <functional>

// Includes:
#include "../ast/node/fdecl.hpp"
#include "../debug/trace.hpp"
#include "../token/token.hpp"


namespace parser {
// Classes:
/*! Abstract parser class provides utilities that a parser would need to
 * implement
 */
class Parser {
  private:
  token::TokenStream m_tokenstream;

  protected:
  DBG_TRACE_INIT()

  /*! Wrapper method for std::make_shared() makes it easy to change smart
   * pointer type later down the line
   */
  template<typename T, typename... Args>
  inline auto make_node(Args&&... t_args) -> std::shared_ptr<T>
  {
    return std::make_shared<T>(std::forward<Args>(t_args)...);
  }

  // m_tokenstream helper methods:
  auto syntax_error(std::string_view t_msg) const -> void;
  auto eos_error(std::string_view t_msg) const -> void;

  auto eos() const -> bool;

  auto check(token::TokenType t_tokentype) -> bool;
  auto next() -> token::Token&;
  auto next_if(token::TokenType t_tokentype) -> bool;
  auto expect(token::TokenType t_tokentype) -> token::Token&;
  auto prev() -> token::Token&;
  auto get_token() const -> token::Token;

  public:
  Parser(token::TokenStream&& t_tokenstream);

  virtual auto parse() -> ast::node::NodePtr = 0;

  virtual ~Parser() = default;
};
} // namespace parser

#endif // CROW_PARSER_PARSER_HPP
