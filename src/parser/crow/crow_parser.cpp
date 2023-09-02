#include "crow_parser.hpp"

// Includes:
#include "../../ast/node/include.hpp"
#include "../../debug/trace.hpp"


// Using statements:
using namespace parser::crow;

using namespace token;

using namespace ast::node;
using namespace ast::node::control;
using namespace ast::node::functions;
using namespace ast::node::lvalue;
using namespace ast::node::operators;
using namespace ast::node::packaging;
using namespace ast::node::rvalue;

// Methods:
CrowParser::CrowParser(TokenStream t_tokenstream)
  : PrattParser{std::move(t_tokenstream)}
{}

auto CrowParser::newline_opt() -> void
{
  DBG_TRACE_FN(VERBOSE);

  while(!eos() && next_if(TokenType::NEWLINE)) {
    DBG_TRACE_PRINT(INFO, "Found 'NEWLINE'");
  }
}

auto CrowParser::terminator() -> void
{
  DBG_TRACE_FN(VERBOSE);

  const auto is_terminator{[this] {
    return check(TokenType::SEMICOLON) || check(TokenType::NEWLINE);
  }};

  if(is_terminator()) {
    next();
  } else {
    syntax_error("Expected at least one 'TERMINATOR'");
  }

  while(!eos()) {
    if(is_terminator()) {
      DBG_TRACE_PRINT(INFO, "Found 'TERMINATOR'");

      next();
    }
  }
}

// TODO: Implement
auto CrowParser::expr_list_opt() -> NodeListPtr
{
  NodeListPtr nodes;

  return nodes;
}

auto CrowParser::loop_statement() -> NodePtr
{
  DBG_TRACE_FN(VERBOSE);
  NodePtr node;

  if(next_if(TokenType::LOOP)) {
    auto [init, cond] = eval_expr();


    NodePtr expr_ptr;
    if(next_if(TokenType::SEMICOLON)) {
      expr_ptr = expr();
    }

    auto body_ptr{body()};

    node = make_node<Loop>(std::move(init), std::move(cond),
                           std::move(expr_ptr), std::move(body_ptr));
  }

  return node;
}

auto CrowParser::decl_expr() -> NodePtr
{
  DBG_TRACE_FN(VERBOSE);
  NodePtr node;

  if(next_if(TokenType::LET)) {
    const auto id{expect(TokenType::IDENTIFIER)};

    if(next_if(TokenType::SEMICOLON)) {
      expect(TokenType::IDENTIFIER);

      // TODO: Implement type inference
    }

    NodePtr expr_ptr;
    if(next_if(TokenType::ASSIGNMENT)) {
      expr_ptr = expr();
    }

    node = make_node<Let>(id.get<std::string>(), std::move(expr_ptr));
  }

  return node;
}

auto CrowParser::eval_expr() -> NodePair
{
  DBG_TRACE_FN(VERBOSE);
  NodePair pair;

  if(auto ptr{decl_expr()}; ptr) {
    expect(TokenType::SEMICOLON);

    pair = {std::move(ptr), expr()};
  } else if(auto ptr{expr()}; ptr) {
    if(next_if(TokenType::SEMICOLON)) {
      pair = {std::move(ptr), expr()};
    } else {
      pair.second = std::move(ptr);
    }
  }

  return pair;
}

auto CrowParser::if_statement() -> NodePtr
{
  DBG_TRACE_FN(VERBOSE);
  NodePtr node;

  if(next_if(TokenType::IF)) {
    auto [init, cond] = eval_expr();
    if(!cond) {
      syntax_error("Expected a conditional");
    }

    auto then_ptr{body()};

    NodeListPtr alt_ptr;
    if(next_if(TokenType::ELSE)) {
      alt_ptr = body();
    }

    node = make_node<If>(std::move(init), std::move(cond), std::move(then_ptr),
                         std::move(alt_ptr));
  }

  return node;
}

auto CrowParser::statement() -> NodePtr
{
  DBG_TRACE_FN(VERBOSE);
  NodePtr node;

  if(auto ptr{if_statement()}; ptr) {
    node = std::move(ptr);
  } else if(auto ptr{loop_statement()}; ptr) {
    node = std::move(ptr);
  }

  return node;
}

auto CrowParser::statement_list() -> NodeListPtr
{
  DBG_TRACE_FN(VERBOSE);
  NodeListPtr nodes{make_node<List>()};

  while(!eos()) {
    if(auto ptr{statement()}; ptr) {
      nodes->push_back(std::move(ptr));
    } else {
      break;
    }

		newline_opt();
  }

  return nodes;
}

/*! The body() should never be optional, or else we will consume newlines
 * unintentionally
 */
auto CrowParser::body() -> NodeListPtr
{
  DBG_TRACE_FN(VERBOSE);
  NodeListPtr nodes;

  // After a list of newlines an accolade most occur
  if(after_newline_list(TokenType::ACCOLADE_OPEN)) {
    newline_opt();
    expect(TokenType::ACCOLADE_OPEN);

    newline_opt();
    if(auto ptr{statement_list()}; ptr) {
      nodes = std::move(ptr);
    }

    expect(TokenType::ACCOLADE_CLOSE);
  } else {
    syntax_error("Expected a body");
  }

  return nodes;
}

auto CrowParser::param_list() -> NodeListPtr
{
  DBG_TRACE_FN(VERBOSE);
  NodeListPtr nodes{make_node<List>()};

  if(check(TokenType::IDENTIFIER)) {
    DBG_TRACE_PRINT(INFO, "Found 'IDENTIFIER'");

    const auto id{get_token().get<std::string>()};
    next();

    nodes->push_back(make_node<Variable>(id));
  }

  while(!eos()) {
    if(next_if(TokenType::COMMA)) {
      DBG_TRACE_PRINT(INFO, "Found ',' 'IDENTIFIER'");

      const auto token{expect(TokenType::IDENTIFIER)};
      const auto id{token.get<std::string>()};

      nodes->push_back(make_node<Variable>(id));
    } else {
      break;
    }
  }

  return nodes;
}

auto CrowParser::return_type_opt() -> NodePtr
{
  DBG_TRACE_FN(VERBOSE);
  NodePtr node;

  if(after_newline_list(TokenType::ARROW)) {
    newline_opt();
    expect(TokenType::ARROW);
    expect(TokenType::IDENTIFIER);

    // TODO: Set node
  }

  return node;
}

auto CrowParser::function() -> NodePtr
{
  DBG_TRACE_FN(VERBOSE);
  NodePtr node;

  if(next_if(TokenType::FUNCTION)) {
    const auto tt_id{expect(TokenType::IDENTIFIER)};
    const auto id{tt_id.get<std::string>()};

    // NodeListPtr params;
    auto params{parens([this] {
      return this->param_list();
    })};

    auto return_type{return_type_opt()};
    auto body_ptr{body()};

    node = make_node<Function>(id, std::move(params), std::move(body_ptr));
  }

  return node;
}

auto CrowParser::import_expr(Import& t_import) -> bool
{
  DBG_TRACE_FN(VERBOSE);
  bool is_import_expr{true};

  const auto token{get_token()};
  if(next_if(TokenType::STRING)) {
    auto str{token.get<std::string>()};
    t_import.add_import(std::move(str));
  } else if(next_if(TokenType::IDENTIFIER)) {
    auto id{token.get<std::string>()};
    expect(TokenType::ASSIGNMENT);
    auto str{expect(TokenType::STRING).get<std::string>()};

    t_import.add_import({str, id});
  } else {
    is_import_expr = false;
  }
  newline_opt();

  return is_import_expr;
}

auto CrowParser::import_list(Import& t_import) -> void
{
  DBG_TRACE_FN(VERBOSE);

  if(!import_expr(t_import)) {
    syntax_error("Expected at least one import");
  }

  while(!eos()) {
    if(!import_expr(t_import)) {
      break;
    }
  }
}

auto CrowParser::import_() -> NodePtr
{
  DBG_TRACE_FN(VERBOSE);
  NodePtr node;

  if(next_if(TokenType::IMPORT)) {
    DBG_TRACE_PRINT(INFO, "Found 'IMPORT'");
    auto import_ptr{make_node<Import>()};
    if(check(TokenType::STRING)) {
      DBG_TRACE_PRINT(INFO, "Found 'STRING'");
      const auto id{get_token()};
      next();

      import_ptr->add_import(id.get<std::string>());
    } else if(next_if(TokenType::PAREN_OPEN)) {
      newline_opt();
      import_list(*import_ptr);
      expect(TokenType::PAREN_CLOSE);
    } else {
      syntax_error("Expected string or an import list");
    }

    node = std::move(import_ptr);
  }

  return node;
}

auto CrowParser::package() -> NodePtr
{
  DBG_TRACE_FN(VERBOSE);
  NodePtr node;

  if(next_if(TokenType::PACKAGE)) {
    DBG_TRACE_PRINT(INFO, "Found 'PACKAGE'");
    const auto id{expect(TokenType::IDENTIFIER)};

    node = make_node<Package>(id.get<std::string>());
  }

  return node;
}

auto CrowParser::item() -> NodePtr
{
  DBG_TRACE_FN(VERBOSE);
  NodePtr node;

  if(auto ptr{package()}; ptr) {
    node = std::move(ptr);
  } else if(auto ptr{import_()}; ptr) {
    node = std::move(ptr);
  } else if(auto ptr{function()}; ptr) {
    node = std::move(ptr);
  }

  return node;
}

// item list exists out of an item followed by a terminator
// Till there are are no more items
auto CrowParser::item_list() -> NodeListPtr
{
  DBG_TRACE_FN(VERBOSE);
  NodeListPtr nodes{make_node<List>()};

  while(!eos()) {
    // Remove newlines before items
    newline_opt();
    if(eos()) {
      break;
    }

    if(auto ptr{item()}; ptr) {
      nodes->push_back(std::move(ptr));
    } else {
      break;
    }
  }

  return nodes;
}

auto CrowParser::program() -> NodeListPtr
{
  DBG_TRACE_FN(VERBOSE);

  return item_list();
}

auto CrowParser::parse() -> NodePtr
{
  return program();
}
