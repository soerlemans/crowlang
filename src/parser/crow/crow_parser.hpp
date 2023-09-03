#ifndef CROW_PARSER_CROW_CROW_PARSER_HPP
#define CROW_PARSER_CROW_CROW_PARSER_HPP

// Includes:
#include "../pratt/pratt_parser.hpp"


namespace parser::crow {
// Namespace aliases:
namespace pkg = ast::node::packaging;

// Aliases:
using NodePair = std::pair<n::NodePtr, n::NodePtr>;

// Classes:
/*! Top down parser of the Crow language.
 * See crow.yy for grammar specification (BNF).
 */
class CrowParser : public pratt::PrattParser {
  public:
  CrowParser(token::TokenStream t_tokenstream);

  // Grammar:
  auto newline_opt() -> void override;
  auto terminator() -> void;

  auto expr_list_opt() -> n::NodeListPtr override;

  virtual auto expr_opt() -> n::NodePtr;
  virtual auto expr_statement() -> n::NodePtr;

  virtual auto decl_expr() -> n::NodePtr;
  virtual auto eval_expr() -> NodePair;

  virtual auto jump_statement() -> n::NodePtr;
  virtual auto loop_statement() -> n::NodePtr;

  virtual auto branch_statement(token::TokenType t_type) -> n::NodePtr;
  virtual auto elif_statement() -> n::NodePtr;
  virtual auto if_statement() -> n::NodePtr;

  virtual auto statement() -> n::NodePtr;
  virtual auto statement_list() -> n::NodeListPtr;

  virtual auto body() -> n::NodeListPtr;

  virtual auto param_list() -> n::NodeListPtr;
  virtual auto return_type_opt() -> n::NodePtr;
  virtual auto function() -> n::NodePtr;

  // Packaging:
  virtual auto import_expr(pkg::Import& t_import) -> bool;
  virtual auto import_list(pkg::Import& t_import) -> void;
  virtual auto import_() -> n::NodePtr;
  virtual auto package() -> n::NodePtr;

  virtual auto item() -> n::NodePtr;
  virtual auto item_list() -> n::NodeListPtr;

  virtual auto program() -> n::NodeListPtr;

  auto parse() -> n::NodePtr override;

  ~CrowParser() override = default;
};

} // namespace parser::crow

#endif // CROW_PARSER_CROW_CROW_PARSER_HPP
