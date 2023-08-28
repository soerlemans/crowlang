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

namespace {
/*! Wrapper method for std::make_shared() makes it easy to change smart pointer
 * type later down the line
 */
template<typename T, typename... Args>
inline auto make_node(Args&&... t_args) -> std::shared_ptr<T>
{
  return std::make_shared<T>(std::forward<Args>(t_args)...);
}
} // namespace


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

auto CrowParser::body() -> NodeListPtr
{
  DBG_TRACE(VERBOSE, "BODY");
  NodeListPtr nodes;

  return nodes;
}

auto CrowParser::param_list() -> NodeListPtr
{
  DBG_TRACE(VERBOSE, "PARAM LIST");
  NodeListPtr nodes;

  return nodes;
}

auto CrowParser::function() -> NodePtr
{
  DBG_TRACE(VERBOSE, "FUNCTION");
  NodePtr node;

  if(next_if(TokenType::FUNCTION)) {
    const auto tt_id{expect(TokenType::IDENTIFIER, "Function identifier")};
    const auto id{tt_id.get<std::string>()};

    NodeListPtr params;
    GROUPING(params, param_list);

    auto body_ptr{body()};

    node = make_node<Function>(id, std::move(params), std::move(body_ptr));
  }

  return node;
}

auto CrowParser::item() -> NodePtr
{
  DBG_TRACE(VERBOSE, "ITEM");
  NodePtr node;

  if(auto ptr{function()}; ptr) {
    node = std::move(ptr);
  }

  return node;
}

// item list exists out of an item followed by a terminator
// Till there are are no more items
auto CrowParser::item_list() -> NodeListPtr
{
  DBG_TRACE(VERBOSE, "ITEM LIST");
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
  DBG_TRACE(VERBOSE, "PROGRAM");

  return item_list();
}

auto CrowParser::parse() -> NodePtr
{
  return program();
}
