#ifndef CROW_PARSER_PARSER_HPP
#define CROW_PARSER_PARSER_HPP

// STL Includes:
#include <functional>

// Includes:
#include "../ast/node/fdecl.hpp"
#include "../debug/trace.hpp"
#include "../token/token.hpp"
#include "../token/tokentype2str.hpp"


// Macros:
#define PARSER_FOUND(t_tokentype, ...)                    \
  do {                                                    \
    const auto str{token::tokentype2str(t_tokentype)};    \
    const auto quoted{std::quoted(str, '\'')};            \
    DBG_TRACE_PRINT(INFO, "Found ", quoted, __VA_ARGS__); \
  } while(false)

namespace parser {
// Namespace aliases:
namespace n = ast::node;

// Aliases:
using ParseFn = std::function<ast::node::NodePtr()>;

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


  // Helper methods for parsing:
  auto syntax_error(std::string_view t_msg) const -> void;
  auto eos_error(std::string_view t_msg) const -> void;

  auto eos() const -> bool;

  auto check(token::TokenType t_type) -> bool;
  auto next() -> token::Token&;
  auto expect(token::TokenType t_type) -> token::Token&;
  auto prev() -> token::Token&;
  auto get_token() const -> token::Token&;

  template<typename... Args>
  auto next_if(Args&&... t_args) -> bool
  {
    const auto is_next{(check(std::forward<Args>(t_args)) || ...)};

    if(is_next) {
      next();
    }

    return is_next;
  }


  auto after_newlines(token::TokenType t_type) -> bool;

  // TODO: create .tpp for these definitions?
  template<typename Fn>
  inline auto surround(const token::TokenType t_open,
                       const token::TokenType t_close, const Fn t_fn)
  {
    using namespace token;

    DBG_TRACE_FN(VERBOSE);

    expect(t_open);
    auto var{t_fn()};
    expect(t_close);

    return var;
  }

  template<typename Fn>
  inline auto parens(const Fn t_fn)
  {
    using namespace token;

    DBG_TRACE_FN(VERBOSE);

    return surround(TokenType::PAREN_OPEN, TokenType::PAREN_CLOSE, t_fn);
  }

  template<typename Fn>
  inline auto accolades(const Fn t_fn)
  {
    using namespace token;

    return surround(TokenType::ACCOLADE_OPEN, TokenType::ACCOLADE_CLOSE, t_fn);
  }

  auto list_of(ParseFn t_fn) -> ast::node::NodeListPtr;

  public:
  Parser(token::TokenStream&& t_tokenstream);

  virtual auto parse() -> n::NodePtr = 0;

  virtual ~Parser() = default;
};
} // namespace parser

#endif // CROW_PARSER_PARSER_HPP
