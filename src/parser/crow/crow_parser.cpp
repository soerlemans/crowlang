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

auto CrowParser::parse() -> NodePtr
{
  NodePtr node;

  return node;
}
