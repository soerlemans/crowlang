#include "pratt_parser.hpp"

// STL Includes:
#include <memory>
#include <stdexcept>

// Absolute Includes:
#include "crow/ast/node/include_nodes.hpp"
#include "crow/debug/log.hpp"

namespace parser::pratt {
// Using Statements:
NODE_USING_ALL_NAMESPACES()

// Methods:
PrattParser::PrattParser(TokenStream&& t_tokenstream)
  : Parser{std::move(t_tokenstream)}
{}

// Prefix parsing:
auto PrattParser::prefix_expr(const TokenType t_type) -> NodePtr
{
  DBG_TRACE_FN(VERBOSE);

  const auto [lbp, rbp] = m_prefix.at(t_type);

  return expr(rbp);
}

auto PrattParser::lvalue() -> NodePtr
{
  DBG_TRACE_FN(VERBOSE);
  NodePtr node;

  const auto token{get_token()};
  if(next_if(TokenType::IDENTIFIER)) {
    const auto id{token.str()};
    DBG_TRACE_PRINT(INFO, "Found 'VARIABLE': ", id);
    node = make_node<Variable>(token.position(), id);
  }

  return node;
}

//! Prefix operator parses prefix increment and decrement
auto PrattParser::literal() -> NodePtr
{
  DBG_TRACE_FN(VERBOSE);
  NodePtr node;

  const auto token{get_token()};
  if(next_if(TokenType::FLOAT)) {
    const auto val{token.double_()};
    PARSER_FOUND(TokenType::FLOAT, " literal: ", val);
    node = make_node<Float>(val);

  } else if(next_if(TokenType::INTEGER)) {
    const auto val{token.int_()};
    PARSER_FOUND(TokenType::INTEGER, " literal: ", val);
    node = make_node<Integer>(val);

  } else if(next_if(TokenType::STRING)) {
    const auto val{token.str()};
    PARSER_FOUND(TokenType::STRING, " literal: ", val);
    node = make_node<String>(val);

  } else if(next_if(TokenType::TRUE)) {
    PARSER_FOUND(TokenType::TRUE);
    node = make_node<Boolean>(true);

  } else if(next_if(TokenType::FALSE)) {
    PARSER_FOUND(TokenType::FALSE);
    node = make_node<Boolean>(false);
  }

  return node;
}

auto PrattParser::grouping() -> NodePtr
{
  DBG_TRACE_FN(VERBOSE);
  NodePtr node;

  if(check(TokenType::PAREN_OPEN)) {
    DBG_TRACE_PRINT(VERBOSE, "Found 'GROUPING'");

    node = parens([this] {
      return this->expr();
    });
  }

  return node;
}

auto PrattParser::negation() -> NodePtr
{
  DBG_TRACE_FN(VERBOSE);
  NodePtr node;

  const auto pos{get_position()};
  if(next_if(TokenType::NOT)) {
    PARSER_FOUND(TokenType::NOT);

    if(auto ptr{prefix_expr(TokenType::NOT)}; ptr) {
      node = make_node<Not>(pos, std::move(ptr));
    } else {
      syntax_error("After a negation (!) an expression must follow");
    }
  }

  return node;
}

//! Parses unary prefixes like having a + or - before an expression
auto PrattParser::unary_prefix() -> NodePtr
{
  DBG_TRACE_FN(VERBOSE);
  NodePtr node;

  const auto token{get_token()};
  if(next_if(TokenType::PLUS, TokenType::MINUS)) {
    DBG_TRACE_PRINT(VERBOSE, "Found 'UNARY PREFIX'");

    NodePtr rhs{prefix_expr(token.type())};
    if(!rhs) {
      syntax_error("Expected an expression after + or -");
    }

    node = make_node<UnaryPrefix>(token.type(), std::move(rhs));
  }

  return node;
}

auto PrattParser::precrement() -> NodePtr
{
  DBG_TRACE_FN(VERBOSE);
  NodePtr node;

  const auto lambda{[&]<typename T>() {
    if(auto ptr{lvalue()}; ptr) {
      node = make_node<T>(std::move(ptr), true);
    } else {
      syntax_error("Expected an lvalue");
    }
  }};

  const auto token{get_token()};
  if(next_if(TokenType::INCREMENT)) {
    PARSER_FOUND(TokenType::INCREMENT, " (pre)");
    lambda.template operator()<Increment>();

  } else if(next_if(TokenType::DECREMENT)) {
    PARSER_FOUND(TokenType::DECREMENT, " (pre)");
    lambda.template operator()<Decrement>();
  }

  return node;
}

//! This function parses function calls
auto PrattParser::function_call() -> NodePtr
{
  DBG_TRACE_FN(VERBOSE);
  NodePtr node;

  const auto token{get_token()};

  if(next_if(TokenType::IDENTIFIER)) {
    // Dont prematurely confuse variables and function calls
    if(!check(TokenType::PAREN_OPEN)) {
      prev();

      return node;
    }

    auto args{parens([this] {
      return this->expr_list_opt();
    })};

    const auto id{token.str()};
    DBG_TRACE_PRINT(INFO, "Found a 'FUNCTION CALL': ", id);

    node = make_node<Call>(id, std::move(args));
  }

  return node;
}

auto PrattParser::prefix() -> NodePtr
{
  DBG_TRACE_FN(VERBOSE);
  NodePtr node;

  if(auto ptr{grouping()}; ptr) {
    node = std::move(ptr);
  } else if(auto ptr{unary_prefix()}; ptr) {
    node = std::move(ptr);
  } else if(auto ptr{negation()}; ptr) {
    node = std::move(ptr);
  } else if(auto ptr{literal()}; ptr) {
    node = std::move(ptr);
  } else if(auto ptr{function_call()}; ptr) {
    node = std::move(ptr);
  } else if(auto ptr{lvalue()}; ptr) {
    node = std::move(ptr);
  } else if(auto ptr{precrement()}; ptr) {
    node = std::move(ptr);
  }

  return node;
}

// Infix parsing:
auto PrattParser::arithmetic(NodePtr& t_lhs, const RhsFn& t_fn) -> NodePtr
{
  DBG_TRACE_FN(VERBOSE);
  NodePtr node;

  const auto pos{get_position()};
  const auto lambda{[&](ArithmeticOp t_op) {
    const auto token{get_token()};
    next();

    if(auto rhs{t_fn(token.type())}; rhs) {
      node = make_node<Arithmetic>(pos, t_op, std::move(t_lhs), std::move(rhs));
    }
  }};

  if(after_newlines(TokenType::ASTERISK)) {
    PARSER_FOUND(TokenType::ASTERISK);
    lambda(ArithmeticOp::MULTIPLY);

  } else if(after_newlines(TokenType::SLASH)) {
    PARSER_FOUND(TokenType::SLASH);
    lambda(ArithmeticOp::DIVIDE);

  } else if(after_newlines(TokenType::PERCENT_SIGN)) {
    PARSER_FOUND(TokenType::PERCENT_SIGN);
    lambda(ArithmeticOp::MODULO);

  } else if(after_newlines(TokenType::PLUS)) {
    PARSER_FOUND(TokenType::PLUS);
    lambda(ArithmeticOp::ADD);

  } else if(after_newlines(TokenType::MINUS)) {
    PARSER_FOUND(TokenType::MINUS);
    lambda(ArithmeticOp::SUBTRACT);
  }

  return node;
}

auto PrattParser::logical(NodePtr& t_lhs, const RhsFn& t_fn) -> NodePtr
{
  DBG_TRACE_FN(VERBOSE);
  NodePtr node;

  const auto pos{get_position()};
  auto lambda{[&]<typename T>() {
    const auto token{get_token()};
    next();

    if(auto rhs{t_fn(token.type())}; rhs) {
      node = make_node<T>(pos, std::move(t_lhs), std::move(rhs));
    }
  }};

  if(after_newlines(TokenType::AND)) {
    PARSER_FOUND(TokenType::AND);
    lambda.template operator()<And>();

  } else if(after_newlines(TokenType::OR)) {
    PARSER_FOUND(TokenType::OR);
    lambda.template operator()<Or>();
  }

  return node;
}

auto PrattParser::comparison(NodePtr& t_lhs, const RhsFn& t_fn) -> NodePtr
{
  DBG_TRACE_FN(VERBOSE);
  NodePtr node;

  if(t_lhs) {
    const auto pos{get_position()};
    const auto lambda{[&](const ComparisonOp t_op) {
      const auto token{get_token()};
      next();

      if(auto rhs{t_fn(token.type())}; rhs) {
        node =
          make_node<Comparison>(pos, t_op, std::move(t_lhs), std::move(rhs));
      }
    }};

    if(after_newlines(TokenType::LESS_THAN)) {
      PARSER_FOUND(TokenType::LESS_THAN);
      lambda(ComparisonOp::LESS_THAN);

    } else if(after_newlines(TokenType::LESS_THAN_EQUAL)) {
      PARSER_FOUND(TokenType::LESS_THAN_EQUAL);
      lambda(ComparisonOp::LESS_THAN_EQUAL);

    } else if(after_newlines(TokenType::EQUAL)) {
      PARSER_FOUND(TokenType::EQUAL);
      lambda(ComparisonOp::EQUAL);

    } else if(after_newlines(TokenType::NOT_EQUAL)) {
      PARSER_FOUND(TokenType::NOT_EQUAL);
      lambda(ComparisonOp::NOT_EQUAL);

    } else if(after_newlines(TokenType::GREATER_THAN)) {
      PARSER_FOUND(TokenType::GREATER_THAN);
      lambda(ComparisonOp::GREATER_THAN);

    } else if(after_newlines(TokenType::GREATER_THAN_EQUAL)) {
      PARSER_FOUND(TokenType::GREATER_THAN_EQUAL);
      lambda(ComparisonOp::GREATER_THAN_EQUAL);
    }
  }

  return node;
}

auto PrattParser::infix(NodePtr& t_lhs, const RhsFn& t_fn) -> NodePtr
{
  DBG_TRACE_FN(VERBOSE);
  NodePtr node;

  if(t_lhs) {
    if(auto ptr{arithmetic(t_lhs, t_fn)}; ptr) {
      node = std::move(ptr);
    } else if(auto ptr{logical(t_lhs, t_fn)}; ptr) {
      node = std::move(ptr);
    } else if(auto ptr{comparison(t_lhs, t_fn)}; ptr) {
      node = std::move(ptr);
    }
  }

  return node;
}

// Expressions:
auto PrattParser::expr(const int t_min_bp) -> NodePtr
{
  DBG_TRACE_FN(VERBOSE);
  NodePtr lhs{prefix()};

  // Infix:
  while(!eos()) {
    const auto rhs_fn{[&](const TokenType t_type) {
      NodePtr rhs;

      const auto [lbp, rbp] = m_infix.at(t_type);
      if(lbp < t_min_bp) {
        prev();
      } else {
        rhs = expr(rbp);
        if(!rhs) {
          syntax_error("Infix operations require a right hand side");
        }
      }

      return rhs;
    }};

    // If we do not find the expression quit
    if(auto ptr{infix(lhs, rhs_fn)}; ptr) {
      lhs = std::move(ptr);
    } else {
      break;
    }
  }

  return lhs;
}
} // namespace parser::pratt
