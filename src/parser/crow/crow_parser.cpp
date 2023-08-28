#include "crow_parser.hpp"

// Includes:
#include "../../ast/node/include.hpp"
#include "../../debug/trace.hpp"


// Macros:
//! Convenvience macro for
#define GROUPING(t_var, t_func)          \
  do {                                   \
    expect(TokenType::PAREN_OPEN, "(");  \
    t_var = t_func();                    \
    expect(TokenType::PAREN_CLOSE, ")"); \
  } while(false)

// Using statements:
using namespace parser::crow;

using namespace token;

using namespace ast::node;
using namespace ast::node::control;
using namespace ast::node::functions;
using namespace ast::node::lvalue;
using namespace ast::node::operators;
using namespace ast::node::rvalue;

CrowParser::CrowParser(TokenStream t_tokenstream)
  : PrattParser{std::move(t_tokenstream)}
{}

auto CrowParser::newline_opt() -> void
{
  DBG_TRACE(VERBOSE, "NEWLINE OPT");

  while(!eos() && next_if(TokenType::NEWLINE)) {
    DBG_TRACE_PRINT(INFO, "Found 'NEWLINE'");
  }
}

// TODO: Implement
auto CrowParser::expr_list_opt() -> NodeListPtr
{
  NodeListPtr nodes;

  return nodes;
}

auto CrowParser::item() -> NodePtr
{
  DBG_TRACE(VERBOSE, "ITEM");
  NodePtr node;

  return node;
}

// item list exists out of an item followed by a terminator
// Till there are are no more items
auto CrowParser::item_list() -> NodeListPtr
{
  DBG_TRACE(VERBOSE, "ITEM LIST");
  NodeListPtr nodes{std::make_shared<List>()};

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
  DBG_TRACE(VERBOSE, "PROGRAM");

  return item_list();
}

auto CrowParser::parse() -> NodePtr
{
  return program();
}
