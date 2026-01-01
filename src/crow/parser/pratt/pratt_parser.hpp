#ifndef CROW_CROW_PARSER_PRATT_PRATT_PARSER_HPP
#define CROW_CROW_PARSER_PRATT_PRATT_PARSER_HPP

// STL Includes:
#include <unordered_map>
#include <utility>

// Absolute Includes:
#include "crow/parser/parser.hpp"
#include "lib/stdtypes.hpp"

// Local Includes:
#include "binding/maps.hpp"

namespace parser::pratt {
class PrattParser;

// Using Statements:
using binding::InfixMap;
using binding::PrefixMap;

//! This type is used to get the right hand side of a binary expressions
using RhsFn = std::function<NodePtr(TokenType)>;
using PrattParserPtr = std::unique_ptr<PrattParser>;

// Classes:
class PrattParser : public Parser {
  private:
  // Note these come from the binding submodule.
  PrefixMap m_prefix;
  InfixMap m_infix;

  public:
  PrattParser(TokenStream&& t_token_stream);

  // TODO: The chain expression stuff needs to be cleaned.
  // Up and gain some clarity.

  // Grammar:
  virtual auto newline_opt() -> void = 0;
  virtual auto expr_list_opt() -> NodeListPtr = 0;

  // Prefix parsing:
  virtual auto prefix_expr(TokenType t_type) -> NodePtr;
  virtual auto lvalue() -> NodePtr;
  virtual auto literal() -> NodePtr;
  virtual auto grouping() -> NodePtr;
  virtual auto unary_prefix() -> NodePtr;
  virtual auto negation() -> NodePtr;
  virtual auto function_call() -> NodePtr;

  virtual auto prefix() -> NodePtr;
  virtual auto prefix_chain_expr() -> NodePtr;

  // Infix parsing:
  virtual auto infix_chain_expr(NodePtr& t_lhs, const RhsFn& t_fn) -> NodePtr;

  virtual auto arithmetic(NodePtr& t_lhs, const RhsFn& t_fn) -> NodePtr;
  virtual auto logical(NodePtr& t_lhs, const RhsFn& t_fn) -> NodePtr;
  virtual auto comparison(NodePtr& t_lhs, const RhsFn& t_fn) -> NodePtr;

  virtual auto infix(NodePtr& t_lhs, const RhsFn& t_fn) -> NodePtr;

  // Expressions:
  virtual auto chain_expr(int t_min_bp = 0) -> NodePtr;
  virtual auto expr(int t_min_bp = 0) -> NodePtr;

  // Lvalue specific:
  virtual auto field_access() -> NodePtr;

  virtual auto lvalue_chain_expr(NodePtr& t_lhs, const RhsFn& t_fn) -> NodePtr;
  virtual auto lvalue_infix(NodePtr& t_lhs, const RhsFn& t_fn) -> NodePtr;

  /*!
   * Continue's a member access chain.
   */
  virtual auto lvalue_member_expr(int t_min_bp = 0) -> NodePtr;

  /*!
   * Generally an expression is universal.
   * But when we are dealing with precedence as the destination for a value.
   * We only allow assignable statements on the left side.
   */
  virtual auto lvalue_expr(int t_min_bp = 0) -> NodePtr;

  virtual ~PrattParser() = default;
};
} // namespace parser::pratt

#endif // CROW_CROW_PARSER_PRATT_PRATT_PARSER_HPP
