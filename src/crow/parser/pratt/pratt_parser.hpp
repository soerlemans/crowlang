#ifndef CROW_CROW_PARSER_PRATT_PRATT_PARSER_HPP
#define CROW_CROW_PARSER_PRATT_PRATT_PARSER_HPP

// STL Includes:
#include <unordered_map>
#include <utility>

// Absolute Includes:
#include "crow/parser/parser.hpp"
#include "lib/stdtypes.hpp"

// Local Includes:
#include "backtrack_guard.hpp"
#include "binding/maps.hpp"

namespace parser::pratt {
// Using Statements:
using binding::InfixMap;
using binding::PrefixMap;

//! This type is used to get the right hand side of a binary expressions
using RhsFn = std::function<NodePtr(TokenType)>;

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
  virtual auto terminator() -> void = 0;
  virtual auto expr_list_opt() -> NodeListPtr = 0;
  virtual auto self() -> NodePtr = 0;

  // Prefix parsing:
  virtual auto prefix_expr(TokenType t_type) -> NodePtr;
  virtual auto lvalue() -> NodePtr;
  virtual auto literal() -> NodePtr;
  virtual auto grouping() -> NodePtr;
  virtual auto unary_prefix() -> NodePtr;
  virtual auto negation() -> NodePtr;
  virtual auto function_call() -> NodePtr;
  virtual auto method_call() -> NodePtr;

  virtual auto prefix() -> NodePtr;
  virtual auto prefix_chain() -> NodePtr;

  // Infix parsing:
  virtual auto infix_chain(NodePtr& t_lhs, const RhsFn& t_fn) -> NodePtr;

  virtual auto arithmetic(NodePtr& t_lhs, const RhsFn& t_fn) -> NodePtr;
  virtual auto logical(NodePtr& t_lhs, const RhsFn& t_fn) -> NodePtr;
  virtual auto comparison(NodePtr& t_lhs, const RhsFn& t_fn) -> NodePtr;

  virtual auto infix(NodePtr& t_lhs, const RhsFn& t_fn) -> NodePtr;

  // Expressions:
  virtual auto chain_expr(int t_min_bp = 0) -> NodePtr;
  virtual auto expr(int t_min_bp = 0) -> NodePtr;

  virtual auto member_access() -> NodePtr;
  virtual auto method_access() -> NodePtr;
  virtual auto field_access() -> NodePtr;

  // Lvalue specific:
  virtual auto lvalue_chain(NodePtr& t_lhs, const RhsFn& t_fn) -> NodePtr;
  virtual auto lvalue_infix(NodePtr& t_lhs, const RhsFn& t_fn) -> NodePtr;

  /*!
   * Continue's a member access chain.
   * Which derives from an lvalue_expr().
   */
  virtual auto lvalue_member_expr(int t_min_bp = 0) -> NodePtr;

  /*!
   * Generally an expression is universal.
   * But when we are dealing with precedence as the destination for a value.
   * We only allow assignable statements on the left hand side.
   * So no assigning to the result of function calls.
   */
  virtual auto lvalue_expr(int t_min_bp = 0) -> NodePtr;

  // Method call specific.
  virtual auto infix_method_call(NodePtr& t_lhs, const RhsFn& t_fn) -> NodePtr;

  /*!
   * The only free standing chain expr which we do not assign to.
   * Is a method_call at the end of a long chain expression.
   * We need backtracking in order to get this to work.
   */
  virtual auto method_call_expr(int t_min_bp = 0) -> NodePtr;

  virtual ~PrattParser() = default;
};
} // namespace parser::pratt

#endif // CROW_CROW_PARSER_PRATT_PRATT_PARSER_HPP
