#ifndef CROW_CROW_PARSER_CROW_CROW_PARSER_HPP
#define CROW_CROW_PARSER_CROW_CROW_PARSER_HPP

// STL Includes:
#include <string>

// Absolute Includes:
#include "crow/parser/pratt/pratt_parser.hpp"
#include "crow/parser/type/type_parser.hpp"

// Local Includes:
#include "context/context_guard.hpp"

namespace parser::crow {
// Using Statements:
using ast::node::packaging::Import;
using context::Context;
using context::ContextStore;
using pratt::PrattParser;
using pratt::PrattParserDelegate;
using type::TypeParser;

// Aliases:
using EvalPair = std::pair<NodePtr, NodePtr>;

template<typename T>
using AccessorFn = std::function<NodePtr(T&)>;

// Classes:
/*!
 * Top down parser of the Crow language.
 * See crow.yy for grammar specification (BNF).
 */
class CrowParser : public Parser {
  private:
  PrattParser m_pratt;
  TypeParser m_type;

  ContextStore m_store;

  protected:
  /*!
   * Check if a certain parsing context is enabled.
   *
   * @note If the passed Context is not enabled throws a @ref SyntaxError.
   *
   * @param[in] t_context Context to check for.
   */
  auto context_check(Context t_context) -> void;

  public:
  CrowParser(TokenStream t_token_stream);

  // Grammar:
  virtual auto newline_opt() -> void;
  virtual auto terminator() -> void;

  // Expressions:
  virtual auto literal_list() -> NodeListPtr;
  virtual auto expr_opt() -> NodePtr;

  virtual auto init_expr(TokenType t_type) -> NodePtr;
  virtual auto let_expr() -> NodePtr;
  virtual auto var_expr() -> NodePtr;
  virtual auto binding_expr() -> NodePtr;
  virtual auto eval_expr() -> EvalPair;

  virtual auto expr_statement() -> NodePtr;

  // Expression lists:
  virtual auto expr_list() -> NodeListPtr;
  virtual auto expr_list_opt() -> NodeListPtr;

  // Result statement:
  virtual auto assignment() -> NodePtr;
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

  // Struct:
  virtual auto member_decl() -> NodePtr;
  virtual auto member_decl_list() -> NodeListPtr;
  virtual auto struct_def() -> NodePtr;

  virtual auto type_def() -> NodePtr;

  virtual auto self() -> NodePtr;

  // Function:
  virtual auto param_list() -> NodeListPtr;
  virtual auto param_list_opt() -> NodeListPtr;

  virtual auto return_type() -> std::string;
  virtual auto return_type_opt() -> std::string;

  virtual auto lambda() -> NodePtr;
  virtual auto function() -> NodePtr;

  virtual auto attribute_item() -> NodePtr;
  virtual auto attribute_item_list() -> NodeListPtr;
  virtual auto attribute_body() -> NodeListPtr;
  virtual auto attribute() -> NodePtr;

  virtual auto declare() -> NodePtr;

  // Import:
  virtual auto import_expr(Import& t_import) -> bool;
  virtual auto import_list(Import& t_import) -> void;
  virtual auto import_() -> NodePtr;

  // Module:
  virtual auto module_decl() -> NodePtr;

  // Items:
  virtual auto item() -> NodePtr;
  virtual auto item_list() -> NodeListPtr;

  virtual auto program() -> NodeListPtr;

  //! Produces AST.
  virtual auto parse() -> NodePtr;

  // Used to expose pratt and type parsing.
  // As the parsers are cyclicly dependent on eachother.
  virtual auto pratt_parse(AccessorFn<PrattParser> t_fn) -> NodePtr;
  virtual auto type_parse(AccessorFn<TypeParser> t_fn) -> NodePtr;

  virtual ~CrowParser() = default;
};

} // namespace parser::crow

#endif // CROW_CROW_PARSER_CROW_CROW_PARSER_HPP
