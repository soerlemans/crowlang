#include "type_parser.hpp"

// STL Includes:
#include <memory>
#include <stdexcept>

// Absolute Includes:
#include "crow/ast/node/include_nodes.hpp"
#include "crow/debug/log.hpp"

namespace parser::type {
// Using Statements:
NODE_USING_ALL_NAMESPACES()

// Methods:
TypeParser::TypeParser(ParserContextPtr t_ctx): Parser{t_ctx}
{}

auto TypeParser::type_name() -> NodePtr
{
  DBG_TRACE_FN(VERBOSE);
  NodePtr node{};

  if(next_if(TokenType::ASTERISK)) {
    PARSER_FOUND(TokenType::ASTERISK);

    // TODO: Assign PointerTypeSpec node.
  }

  return node;
}

auto TypeParser::type_pointer() -> NodePtr
{
  DBG_TRACE_FN(VERBOSE);
  NodePtr node{};

  if(next_if(TokenType::IDENTIFIER)) {
    PARSER_FOUND(TokenType::IDENTIFIER);

    // TODO: TypeName pointer node.
  }

  return node;
}

auto TypeParser::type_expr() -> NodePtr
{
  DBG_TRACE_FN(VERBOSE);
  NodePtr node{};

  if(auto ptr{type_pointer()}; ptr) {
    node = std::move(ptr);
  } else if(auto ptr{type_name()}; ptr) {
    node = std::move(ptr);
  }

  return node;
}

} // namespace parser::type
