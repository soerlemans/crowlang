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

// Expression terminals:
//! Parses unary prefixes like having a + or - before an expression
auto PrattParser::unary_prefix(const PrattFunc& t_fn) -> NodePtr
{
  DBG_TRACE(VERBOSE, "UNARY PREFIX");
  NodePtr node;

  switch(const auto token{next()}; token.type()) {
    case TokenType::PLUS:
      [[fallthrough]];
    case TokenType::MINUS: {
      DBG_TRACE(VERBOSE, "Found UNARY PREFIX");

      NodePtr rhs{t_fn(token.type())};
      if(!rhs) {
        syntax_error("Expected an expression after + or -");
      }

      node = std::make_shared<UnaryPrefix>(token.type(), std::move(rhs));
      break;
    }

    default:
      prev();
      break;
  }

  return node;
}

// TODO: Have this also handle multidimensional 'in' statements?
// TODO: Create a function that extracts expressions from in between '(', ')'
auto PrattParser::grouping() -> NodePtr
{
  DBG_TRACE(VERBOSE, "GROUPING");
  NodePtr node;

  if(next_if(TokenType::PAREN_OPEN)) {
    DBG_TRACE_PRINT(VERBOSE, "Found GROUPING");

    node = std::make_shared<Grouping>(expr());
    expect(TokenType::PAREN_CLOSE);
  }

  return node;
}

auto PrattParser::negation(const PrattFunc& t_expr) -> NodePtr
{
  DBG_TRACE(VERBOSE, "NEGATION");
  NodePtr node;

  if(next_if(TokenType::NOT)) {
    DBG_TRACE_PRINT(INFO, "Found '!'");
    if(auto ptr{t_expr(TokenType::NOT)}; ptr) {
      node = std::make_shared<Not>(std::move(ptr));
    } else {
      syntax_error("After a negation (!) an expression must follow");
    }
  }

  return node;
}

auto PrattParser::literal() -> NodePtr
{
  DBG_TRACE(VERBOSE, "LITERAL");
  NodePtr node;

  switch(const auto token{next()}; token.type()) {
    // TODO: Token in the grammar calls for NUMBER? These are not treated
    // differently?
    case TokenType::FLOAT:
      DBG_TRACE_PRINT(INFO, "Found FLOAT literal");
      node = std::make_shared<Float>(token.get<double>());
      break;

      // TODO: Take a look at this later when dealing with typeinference
      // case TokenType::HEX:
      //   [[fallthrough]];
      // case TokenType::INTEGER:
      //   DBG_TRACE_PRINT(INFO, "Found INTEGER literal: ");
      //   node = std::make_shared<Integer>(token.get<int>());
      // break;

    case TokenType::STRING:
      DBG_TRACE_PRINT(INFO, "Found STRING literal: ", token.get<std::string>());
      node = std::make_shared<String>(token.get<std::string>());
      break;

    default:
      prev();
      break;
  }

  return node;
}

auto PrattParser::lvalue() -> NodePtr
{
  DBG_TRACE(VERBOSE, "LVALUE");
  NodePtr node;

  const auto token{next()};
  switch(token.type()) {
    case TokenType::IDENTIFIER: {
      const auto name{token.get<std::string>()};
      // We really dont expect these next_tokens to fail
      DBG_TRACE_PRINT(INFO, "Found VARIABLE: ", name);
      node = std::make_shared<Variable>(name);
      break;
    }

    default:
      prev();
      break;
  }

  return node;
}

// TODO: We should use PostfixMap?
auto PrattParser::postcrement(NodePtr& t_lhs) -> NodePtr
{
  DBG_TRACE(VERBOSE, "POSTCREMENT");
  NodePtr node;

  switch(next().type()) {
    case TokenType::INCREMENT:
      DBG_TRACE_PRINT(INFO, "Found INCREMENT++");
      node = std::make_shared<Increment>(std::move(t_lhs), false);
      break;

    case TokenType::DECREMENT:
      DBG_TRACE_PRINT(INFO, "Found DECREMENT--");
      node = std::make_shared<Decrement>(std::move(t_lhs), false);
      break;

    default:
      prev();
      break;
  }

  return node;
}

//! Prefix operator parses prefix increment and decrement
auto PrattParser::precrement() -> NodePtr
{
  DBG_TRACE(VERBOSE, "PREFIX OPERATOR");
  NodePtr node;

  const auto lambda{[&]<typename T>() {
    if(auto ptr{lvalue()}; ptr) {
      node = std::make_shared<T>(std::move(ptr), true);
    } else {
      // TODO: Error handling
    }
  }};

  switch(next().type()) {
    case TokenType::INCREMENT: {
      DBG_TRACE_PRINT(INFO, "Found ++INCREMENT");
      lambda.template operator()<Increment>();
      break;
    }

    case TokenType::DECREMENT: {
      DBG_TRACE_PRINT(INFO, "Found --DECREMENT");
      lambda.template operator()<Decrement>();
      break;
    }

    default:
      prev();
      break;
  }

  return node;
}


// This function parses function calls, it parses builtin functions as well as
// User defined
auto PrattParser::function_call() -> NodePtr
{
  DBG_TRACE(VERBOSE, "FUNCTION CALL");
  NodePtr node;

  switch(const auto token{next()}; token.type()) {
    case TokenType::IDENTIFIER: {
      expect(TokenType::PAREN_OPEN);
      NodeListPtr args{expr_list_opt()};
      expect(TokenType::PAREN_CLOSE);

      auto name{token.get<std::string>()};
      DBG_TRACE_PRINT(INFO, "Found a FUNCTION CALL: ", name);

      node = std::make_shared<FunctionCall>(std::move(name), std::move(args));
      break;
    }

    default:
      prev();
      break;
  }

  return node;
}

auto PrattParser::arithmetic(NodePtr& t_lhs, const PrattFunc& t_fn) -> NodePtr
{
  DBG_TRACE(VERBOSE, "ARITHMETIC");
  NodePtr node;

  const auto token{next()};
  const auto lambda{[&](ArithmeticOp t_op) {
    if(auto rhs{t_fn(token.type())}; rhs) {
      node =
        std::make_shared<Arithmetic>(t_op, std::move(t_lhs), std::move(rhs));
    }
  }};

  // TODO: Maybe define a macro to do this cleanly?
  switch(token.type()) {
    case TokenType::ASTERISK:
      DBG_TRACE_PRINT(INFO, "Found 'MULTIPLICATION'");
      lambda(ArithmeticOp::MULTIPLY);
      break;

    case TokenType::SLASH:
      DBG_TRACE_PRINT(INFO, "Found 'DIVISION'");
      lambda(ArithmeticOp::DIVIDE);
      break;

    case TokenType::PERCENT_SIGN:
      DBG_TRACE_PRINT(INFO, "Found 'MODULO'");
      lambda(ArithmeticOp::MODULO);
      break;

    case TokenType::PLUS:
      DBG_TRACE_PRINT(INFO, "Found 'ADDITION'");
      lambda(ArithmeticOp::ADD);
      break;

    case TokenType::MINUS:
      DBG_TRACE_PRINT(INFO, "Found 'SUBTRACTION'");
      lambda(ArithmeticOp::SUBTRACT);
      break;

    default:
      prev();
      break;
  }

  return node;
}

auto PrattParser::logical(NodePtr& t_lhs, const PrattFunc& t_fn) -> NodePtr
{
  DBG_TRACE(VERBOSE, "LOGICAL");
  NodePtr node;

  const auto token{next()};
  auto lambda{[&]<typename T>() {
    newline_opt();
    if(auto rhs{t_fn(token.type())}; rhs) {
      node = std::make_shared<T>(std::move(t_lhs), std::move(rhs));
    }
  }};

  switch(token.type()) {
    case TokenType::AND:
      DBG_TRACE_PRINT(INFO, "Found '&&'");
      lambda.template operator()<And>();
      break;

    case TokenType::OR:
      DBG_TRACE_PRINT(INFO, "Found '||'");
      lambda.template operator()<Or>();
      break;

    default:
      prev();
      break;
  }

  return node;
}

auto PrattParser::assignment(NodePtr& t_lhs, const PrattFunc& t_fn) -> NodePtr
{
  DBG_TRACE(VERBOSE, "ASSIGNMENT");
  NodePtr node;

  if(t_lhs) {
    // TODO: Create an actual function for this that we can call instead of
    // Defining a separate lambda in each function
    const auto token{next()};
    const auto lambda{[&](AssignmentOp t_op) {
      auto rhs{t_fn(token.type())};
      if(rhs) {
        node =
          std::make_shared<Assignment>(t_op, std::move(t_lhs), std::move(rhs));
      }
    }};

    switch(token.type()) {
      case TokenType::MUL_ASSIGN:
        DBG_TRACE_PRINT(INFO, "Found '*='");
        lambda(AssignmentOp::MULTIPLY);
        break;

      case TokenType::DIV_ASSIGN:
        DBG_TRACE_PRINT(INFO, "Found '/='");
        lambda(AssignmentOp::DIVIDE);
        break;

      case TokenType::MOD_ASSIGN:
        DBG_TRACE_PRINT(INFO, "Found '%='");
        lambda(AssignmentOp::MODULO);
        break;

      case TokenType::ADD_ASSIGN:
        DBG_TRACE_PRINT(INFO, "Found '+='");
        lambda(AssignmentOp::ADD);
        break;

      case TokenType::SUB_ASSIGN:
        DBG_TRACE_PRINT(INFO, "Found '-='");
        lambda(AssignmentOp::SUBTRACT);
        break;

      case TokenType::ASSIGNMENT:
        DBG_TRACE_PRINT(INFO, "Found '='");
        lambda(AssignmentOp::REGULAR);
        break;

      default:
        prev();
        break;
    }
  }

  return node;
}

auto PrattParser::comparison(NodePtr& t_lhs, const PrattFunc& t_fn) -> NodePtr
{
  DBG_TRACE(VERBOSE, "COMPARISON");
  NodePtr node;

  if(t_lhs) {
    const auto token{next()};
    const auto lambda{[&](ComparisonOp t_op) {
      auto rhs{t_fn(token.type())};
      if(rhs) {
        node =
          std::make_shared<Comparison>(t_op, std::move(t_lhs), std::move(rhs));
      }
    }};

    switch(token.type()) {
      case TokenType::LESS_THAN:
        DBG_TRACE_PRINT(INFO, "Found '<'");
        lambda(ComparisonOp::LESS_THAN);
        break;

      case TokenType::LESS_THAN_EQUAL:
        DBG_TRACE_PRINT(INFO, "Found '<='");
        lambda(ComparisonOp::LESS_THAN_EQUAL);
        break;

      case TokenType::EQUAL:
        DBG_TRACE_PRINT(INFO, "Found '=='");
        lambda(ComparisonOp::EQUAL);
        break;

      case TokenType::NOT_EQUAL:
        DBG_TRACE_PRINT(INFO, "Found '!='");
        lambda(ComparisonOp::NOT_EQUAL);
        break;

      case TokenType::GREATER_THAN:
        DBG_TRACE_PRINT(INFO, "Found '>'");
        lambda(ComparisonOp::GREATER_THAN);
        break;

      case TokenType::GREATER_THAN_EQUAL:
        DBG_TRACE_PRINT(INFO, "Found '>='");
        lambda(ComparisonOp::GREATER_THAN_EQUAL);
        break;

      default:
        prev();
        break;
    }
  }

  return node;
}

auto PrattParser::infix(NodePtr& t_lhs, const PrattFunc& t_fn) -> NodePtr
{
  DBG_TRACE(VERBOSE, "UNIVERSAL EXPR");
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
  DBG_TRACE(VERBOSE, "EXPR");
  NodePtr lhs;

  const auto prefix{[&](TokenType t_type) {
    const auto [lbp, rbp] = m_prefix.at(t_type);

    return expr(rbp);
  }};

  if(auto ptr{grouping()}; ptr) {
    lhs = std::move(ptr);
  } else if(auto ptr{negation(prefix)}; ptr) {
    lhs = std::move(ptr);
  } else if(auto ptr{literal()}; ptr) {
    lhs = std::move(ptr);
  } else if(auto ptr{lvalue()}; ptr) {
    lhs = std::move(ptr);

    ptr = postcrement(lhs);
    if(ptr) {
      lhs = std::move(ptr);
    }
  } else if(auto ptr{precrement()}; ptr) {
    lhs = std::move(ptr);
  } else if(auto ptr{function_call()}; ptr) {
    lhs = std::move(ptr);
  }

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
