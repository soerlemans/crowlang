#ifndef CROW_CROW_PARSER_PRATT_PRATT_PARSER_HPP
#define CROW_CROW_PARSER_PRATT_PRATT_PARSER_HPP

// STL Includes:
#include <unordered_map>
#include <utility>

// Absolute Includes:
#include "crow/parser/parser.hpp"
#include "lib/types.hpp"

// Local Includes:
#include "binding/maps.hpp"

namespace parser::pratt {
// Using Declarations:
using binding::InfixMap;
using binding::PostfixMap;
using binding::PrefixMap;

//! This type is used to get the right hand side of a binary expressions
using RhsFn = std::function<NodePtr(TokenType)>;

// Classes:
class PrattParser : public Parser {
  private:
  // Note these come from the binding submodule.
  PrefixMap m_prefix;
  InfixMap m_infix;
  PostfixMap m_postfix;

  public:
  PrattParser(TokenStream&& t_tokenstream);

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
  virtual auto precrement() -> NodePtr;
  virtual auto function_call() -> NodePtr;

  virtual auto prefix() -> NodePtr;

  // Infix parsing:
  virtual auto arithmetic(NodePtr& t_lhs, const RhsFn& t_fn) -> NodePtr;
  virtual auto logical(NodePtr& t_lhs, const RhsFn& t_fn) -> NodePtr;
  virtual auto comparison(NodePtr& t_lhs, const RhsFn& t_fn) -> NodePtr;

  virtual auto infix(NodePtr& t_lhs, const RhsFn& t_fn) -> NodePtr;

  // Expressions:
  virtual auto expr(int t_min_bp = 0) -> NodePtr;

  virtual ~PrattParser() = default;
};
} // namespace parser::pratt

#endif // CROW_CROW_PARSER_PRATT_PRATT_PARSER_HPP
