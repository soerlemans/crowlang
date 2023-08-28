#ifndef CROW_PARSER_CROW_CROW_PARSER_HPP
#define CROW_PARSER_CROW_CROW_PARSER_HPP

// Includes:
#include "../pratt/pratt_parser.hpp"


namespace parser::crow {

// Classes:
/*! Top down parser of the Crow language.
 * See crow.yy for grammar specification (BNF).
 */
class CrowParser : public pratt::PrattParser {
  public:
  CrowParser(token::TokenStream t_tokenstream);

  // Grammar:
  auto newline_opt() -> void override;

  auto expr_list_opt() -> ast::node::NodeListPtr override;

  virtual auto item() -> ast::node::NodePtr;
  virtual auto item_list() -> ast::node::NodeListPtr;

  virtual auto program() -> ast::node::NodeListPtr;

  auto parse() -> ast::node::NodePtr override;

  ~CrowParser() override = default;
};

} // namespace parser::crow

#endif // CROW_PARSER_CROW_CROW_PARSER_HPP
