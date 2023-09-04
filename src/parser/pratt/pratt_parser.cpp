#include "pratt_parser.hpp"

// STL Includes:
#include <memory>
#include <stdexcept>

// Includes:
#include "../../ast/node/include.hpp"
#include "../../debug/log.hpp"

// Using statements:
using namespace parser::pratt;
using namespace token;
using namespace ast::node;
using namespace ast::node::operators;
using namespace ast::node::rvalue;
using namespace ast::node::lvalue;
using namespace ast::node::functions;

// Methods:
PrattParser::PrattParser(token::TokenStream&& t_tokenstream)
  : Parser{std::move(t_tokenstream)}
{}

// Prefix parsing:
auto PrattParser::lvalue() -> NodePtr
{
  DBG_TRACE_FN(VERBOSE);
  NodePtr node;

  const auto token{get_token()};
  if(next_if(TokenType::IDENTIFIER)) {
    const auto id{token.get<std::string>()};
    DBG_TRACE_PRINT(INFO, "Found 'VARIABLE': ", id);
    node = make_node<Variable>(id);
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
    DBG_TRACE_PRINT(INFO, "Found FLOAT literal: ");
    node = make_node<Float>(token.get<double>());
  } else if(next_if(TokenType::INTEGER)) {
    DBG_TRACE_PRINT(INFO, "Found INTEGER literal: ");
    node = make_node<Integer>(token.get<int>());
  } else if(next_if(TokenType::STRING)) {
    DBG_TRACE_PRINT(INFO, "Found STRING literal: ", token.get<std::string>());
    node = make_node<String>(token.get<std::string>());
  }

  return node;
}


auto PrattParser::grouping() -> NodePtr
{
  DBG_TRACE_FN(VERBOSE);
  NodePtr node;

  if(check(TokenType::PAREN_OPEN)) {
    DBG_TRACE_PRINT(VERBOSE, "Found GROUPING");

    node = parens([this] {
      return this->expr();
    });
  }

  return node;
}

auto PrattParser::negation(const PrattFunc& t_expr) -> NodePtr
{
  DBG_TRACE_FN(VERBOSE);
  NodePtr node;

  if(next_if(TokenType::NOT)) {
    DBG_TRACE_PRINT(INFO, "Found '!'");
    if(auto ptr{t_expr(TokenType::NOT)}; ptr) {
      node = make_node<Not>(std::move(ptr));
    } else {
      syntax_error("After a negation (!) an expression must follow");
    }
  }

  return node;
}

//! Parses unary prefixes like having a + or - before an expression
auto PrattParser::unary_prefix(const PrattFunc& t_fn) -> NodePtr
{
  DBG_TRACE_FN(VERBOSE);
  NodePtr node;

  const auto token{get_token()};
  if(check(TokenType::PLUS) || check(TokenType::MINUS)) {
    next();
    DBG_TRACE_PRINT(VERBOSE, "Found UNARY PREFIX");

    NodePtr rhs{t_fn(token.type())};
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
    DBG_TRACE_PRINT(INFO, "Found ++INCREMENT");
    lambda.template operator()<Increment>();
  } else if(next_if(TokenType::DECREMENT)) {

    DBG_TRACE_PRINT(INFO, "Found --DECREMENT");
    lambda.template operator()<Decrement>();
  }

  return node;
}


// This function parses function calls, it parses builtin functions as well as
// User defined
auto PrattParser::function_call() -> NodePtr
{
  DBG_TRACE_FN(VERBOSE);
  NodePtr node;

  const auto token{get_token()};

  if(next_if(TokenType::IDENTIFIER)) {
    auto args{parens([this] {
      return this->expr_list_opt();
    })};

    auto id{token.get<std::string>()};
    DBG_TRACE_PRINT(INFO, "Found a 'FUNCTION CALL': ", id);

    node = make_node<FunctionCall>(std::move(id), std::move(args));
  }

  return node;
}

auto PrattParser::prefix(const PrattFunc& t_fn) -> NodePtr
{
  DBG_TRACE_FN(VERBOSE);
  NodePtr node;

  if(auto ptr{grouping()}; ptr) {
    node = std::move(ptr);
  } else if(auto ptr{negation(t_fn)}; ptr) {
    node = std::move(ptr);
  } else if(auto ptr{literal()}; ptr) {
    node = std::move(ptr);
  } else if(auto ptr{lvalue()}; ptr) {
    node = std::move(ptr);
  } else if(auto ptr{precrement()}; ptr) {
    node = std::move(ptr);
  } else if(auto ptr{function_call()}; ptr) {
    node = std::move(ptr);
  }

  return node;
}

// Infix parsing:
auto PrattParser::arithmetic(NodePtr& t_lhs, const PrattFunc& t_fn) -> NodePtr
{
  DBG_TRACE_FN(VERBOSE);
  NodePtr node;

  const auto token{get_token()};
  const auto lambda{[&](ArithmeticOp t_op) {
		newline_opt();
    if(auto rhs{t_fn(token.type())}; rhs) {
      node = make_node<Arithmetic>(t_op, std::move(t_lhs), std::move(rhs));
    }
  }};

  // TODO: This code can be made shorter
  if(next_if(TokenType::ASTERISK)) {
    DBG_TRACE_PRINT(INFO, "Found 'MULTIPLICATION'");
    lambda(ArithmeticOp::MULTIPLY);
  } else if(next_if(TokenType::SLASH)) {
    DBG_TRACE_PRINT(INFO, "Found 'DIVISION'");
    lambda(ArithmeticOp::DIVIDE);
  } else if(next_if(TokenType::PERCENT_SIGN)) {
    DBG_TRACE_PRINT(INFO, "Found 'MODULO'");
    lambda(ArithmeticOp::MODULO);
  } else if(next_if(TokenType::PLUS)) {
    DBG_TRACE_PRINT(INFO, "Found 'ADDITION'");
    lambda(ArithmeticOp::ADD);
  } else if(next_if(TokenType::MINUS)) {
    DBG_TRACE_PRINT(INFO, "Found 'SUBTRACTION'");
    lambda(ArithmeticOp::SUBTRACT);
  }

  return node;
}

auto PrattParser::logical(NodePtr& t_lhs, const PrattFunc& t_fn) -> NodePtr
{
  DBG_TRACE_FN(VERBOSE);
  NodePtr node;

  const auto token{get_token()};
  auto lambda{[&]<typename T>() {
    newline_opt();
    if(auto rhs{t_fn(token.type())}; rhs) {
      node = make_node<T>(std::move(t_lhs), std::move(rhs));
    }
  }};

  if(next_if(TokenType::AND)) {
    DBG_TRACE_PRINT(INFO, "Found '&&'");
    lambda.template operator()<And>();
  } else if(next_if(TokenType::AND)) {
    DBG_TRACE_PRINT(INFO, "Found '||'");
    lambda.template operator()<Or>();
  }

  return node;
}

auto PrattParser::assignment(NodePtr& t_lhs, const PrattFunc& t_fn) -> NodePtr
{
  DBG_TRACE_FN(VERBOSE);
  NodePtr node;

  if(t_lhs) {
    // TODO: Create an actual function for this that we can call instead of
    // Defining a separate lambda in each function
    const auto token{get_token()};
    const auto lambda{[&](AssignmentOp t_op) {
			newline_opt();
      auto rhs{t_fn(token.type())};
      if(rhs) {
        node = make_node<Assignment>(t_op, std::move(t_lhs), std::move(rhs));
      }
    }};

    if(next_if(TokenType::MUL_ASSIGN)) {
      DBG_TRACE_PRINT(INFO, "Found '*='");
      lambda(AssignmentOp::MULTIPLY);
    } else if(next_if(TokenType::DIV_ASSIGN)) {
      DBG_TRACE_PRINT(INFO, "Found '/='");
      lambda(AssignmentOp::DIVIDE);
    } else if(next_if(TokenType::MOD_ASSIGN)) {
      DBG_TRACE_PRINT(INFO, "Found '%='");
      lambda(AssignmentOp::MODULO);
    } else if(next_if(TokenType::ADD_ASSIGN)) {
      DBG_TRACE_PRINT(INFO, "Found '+='");
      lambda(AssignmentOp::ADD);
    } else if(next_if(TokenType::SUB_ASSIGN)) {
      DBG_TRACE_PRINT(INFO, "Found '-='");
      lambda(AssignmentOp::SUBTRACT);
    } else if(next_if(TokenType::ASSIGNMENT)) {
      DBG_TRACE_PRINT(INFO, "Found '='");
      lambda(AssignmentOp::REGULAR);
    }
  }

  return node;
}

auto PrattParser::comparison(NodePtr& t_lhs, const PrattFunc& t_fn) -> NodePtr
{
  DBG_TRACE_FN(VERBOSE);
  NodePtr node;

  if(t_lhs) {
    const auto token{get_token()};
    const auto lambda{[&](ComparisonOp t_op) {
			newline_opt();
      auto rhs{t_fn(token.type())};
      if(rhs) {
        node = make_node<Comparison>(t_op, std::move(t_lhs), std::move(rhs));
      }
    }};

    if(next_if(TokenType::LESS_THAN)) {
      DBG_TRACE_PRINT(INFO, "Found '<'");
      lambda(ComparisonOp::LESS_THAN);
    } else if(next_if(TokenType::LESS_THAN_EQUAL)) {
      DBG_TRACE_PRINT(INFO, "Found '<='");
      lambda(ComparisonOp::LESS_THAN_EQUAL);
    } else if(next_if(TokenType::EQUAL)) {
      DBG_TRACE_PRINT(INFO, "Found '=='");
      lambda(ComparisonOp::EQUAL);
    } else if(next_if(TokenType::NOT_EQUAL)) {
      DBG_TRACE_PRINT(INFO, "Found '!='");
      lambda(ComparisonOp::NOT_EQUAL);
    } else if(next_if(TokenType::GREATER_THAN)) {
      DBG_TRACE_PRINT(INFO, "Found '>'");
      lambda(ComparisonOp::GREATER_THAN);
    } else if(next_if(TokenType::GREATER_THAN_EQUAL)) {
      DBG_TRACE_PRINT(INFO, "Found '>='");
      lambda(ComparisonOp::GREATER_THAN_EQUAL);
    }
  }

  return node;
}

auto PrattParser::infix(NodePtr& t_lhs, const PrattFunc& t_fn) -> NodePtr
{
  DBG_TRACE_FN(VERBOSE);
  NodePtr node;

  if(t_lhs) {
    if(auto ptr{arithmetic(t_lhs, t_fn)}; ptr) {
      node = std::move(ptr);
    } else if(auto ptr{logical(t_lhs, t_fn)}; ptr) {
      node = std::move(ptr);
    } else if(auto ptr{assignment(t_lhs, t_fn)}; ptr) {
      node = std::move(ptr);
    } else if(auto ptr{comparison(t_lhs, t_fn)}; ptr) {
      node = std::move(ptr);
    }
  }

  return node;
}

// Grammar:
auto PrattParser::expr(const int t_min_bp) -> NodePtr
{
  DBG_TRACE_FN(VERBOSE);
  NodePtr lhs;

  const auto prefix_fn{[&](TokenType t_type) {
    const auto [lbp, rbp] = m_prefix.at(t_type);

    return expr(rbp);
  }};

  lhs = prefix(prefix_fn);

  // Infix:
  while(!eos()) {
    const auto infix_fn{[&](TokenType t_type) {
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
    if(auto ptr{infix(lhs, infix_fn)}; ptr) {
      lhs = std::move(ptr);
    } else {
      break;
    }
  }

  return lhs;
}
