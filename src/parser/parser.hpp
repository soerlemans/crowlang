#ifndef CROW_PARSER_PARSER_HPP
#define CROW_PARSER_PARSER_HPP

// STL Includes:
#include <functional>

// Includes:
#include "../ast/node/fdecl.hpp"
#include "../debug/trace.hpp"
#include "../token/token.hpp"


namespace parser {
// Namespace aliases:
namespace n = ast::node;

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

  template<typename T>
  inline auto parens(const T t_fn)
  {
    using namespace token;

    DBG_TRACE_FN(VERBOSE);

    expect(TokenType::PAREN_OPEN);
    auto var{t_fn()};
    expect(TokenType::PAREN_CLOSE);

    return var;
  }

  // Helper methods for parsing:
  auto syntax_error(std::string_view t_msg) const -> void;
  auto eos_error(std::string_view t_msg) const -> void;

  auto eos() const -> bool;

  auto check(token::TokenType t_type) -> bool;
  auto next() -> token::Token&;
  auto next_if(token::TokenType t_type) -> bool;
  auto expect(token::TokenType t_type) -> token::Token&;
  auto prev() -> token::Token&;
  auto get_token() const -> token::Token&;

  auto after_newlines(token::TokenType t_type) -> bool;

  public:
  Parser(token::TokenStream&& t_tokenstream);

  virtual auto parse() -> n::NodePtr = 0;

  virtual ~Parser() = default;
};
} // namespace parser

#endif // CROW_PARSER_PARSER_HPP
