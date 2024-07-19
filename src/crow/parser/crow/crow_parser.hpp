#ifndef CROW_CROW_PARSER_CROW_CROW_PARSER_HPP
#define CROW_CROW_PARSER_CROW_CROW_PARSER_HPP

// STL Includes:
#include <string>

// Absolute Includes:
#include "crow/parser/pratt/pratt_parser.hpp"

namespace parser::crow {
// Using Statements:
using ast::node::packaging::Import;

// Aliases:
using EvalPair = std::pair<NodePtr, NodePtr>;

// Classes:
/*!
 * Top down parser of the Crow language.
 * See crow.yy for grammar specification (BNF).
 */
class CrowParser : public pratt::PrattParser {
  public:
  CrowParser(TokenStream t_tokenstream);

  // Grammar:
  auto newline_opt() -> void override;
  virtual auto terminator() -> void;

  // Expressions:
  virtual auto expr_opt() -> NodePtr;

  virtual auto init_expr(TokenType t_type) -> NodePtr;
  virtual auto let_expr() -> NodePtr;
  virtual auto var_expr() -> NodePtr;
  virtual auto decl_expr() -> NodePtr;
  virtual auto eval_expr() -> EvalPair;

  virtual auto expr_statement() -> NodePtr;

  // Expression lists:
  virtual auto expr_list() -> NodeListPtr;
  auto expr_list_opt() -> NodeListPtr override;

  // Result statement:
  virtual auto assignment() -> NodePtr;
	virtual auto postcrement() -> NodePtr;
  virtual auto result_statement() -> NodePtr;

  // Jump statements:
  virtual auto jump_statement() -> NodePtr;

  // Loop statements:
  virtual auto loop_statement() -> NodePtr;

  // Branch statements:
  virtual auto branch_statement(TokenType t_type) -> NodePtr;
  virtual auto if_statement() -> NodePtr;
  virtual auto elif_statement() -> NodePtr;

  // Statements:
  virtual auto statement() -> NodePtr;
  virtual auto statement_list() -> NodeListPtr;

  // Body:
  virtual auto body() -> NodeListPtr;

  // Interface:
  virtual auto method_decl() -> NodePtr;
  virtual auto method_decl_list() -> NodeListPtr;
  virtual auto interface_def() -> NodePtr;

  // Struct:
  virtual auto member_decl() -> NodePtr;
  virtual auto member_decl_list() -> NodeListPtr;
  virtual auto struct_def() -> NodePtr;

  virtual auto type_def() -> NodePtr;

  // Def:
  virtual auto def_list() -> NodeListPtr;
  virtual auto def_block() -> NodePtr;

  // Function:
  virtual auto param_list() -> NodeListPtr;
  virtual auto param_list_opt() -> NodeListPtr;

  virtual auto return_type() -> std::string;
  virtual auto return_type_opt() -> std::string;

  virtual auto lambda() -> NodePtr;
  virtual auto function() -> NodePtr;

  // Import:
  virtual auto import_expr(Import& t_import) -> bool;
  virtual auto import_list(Import& t_import) -> void;
  virtual auto import_() -> NodePtr;

  // Package:
  virtual auto module_() -> NodePtr;

  virtual auto item() -> NodePtr;
  virtual auto item_list() -> NodeListPtr;

  virtual auto program() -> NodeListPtr;

  auto parse() -> NodePtr override;

  virtual ~CrowParser() = default;
};

} // namespace parser::crow

#endif // CROW_CROW_PARSER_CROW_CROW_PARSER_HPP
