#include "type_parser.hpp"

// STL Includes:
#include <memory>
#include <stdexcept>

// Absolute Includes:
#include "acris/ast/node/include_nodes.hpp"
#include "acris/debug/log.hpp"

namespace parser::type {
// Using Statements:
NODE_USING_ALL_NAMESPACES()

// Methods:
TypeParser::TypeParser(ParserContextPtr t_ctx): Parser{t_ctx}
{}

auto TypeParser::type_pointer() -> NodePtr
{
  DBG_TRACE_FN(VERBOSE);
  NodePtr node{};

  const auto token{get_token()};
  if(next_if(TokenType::ASTERISK)) {
    PARSER_FOUND(TokenType::ASTERISK);

    const auto pos{token.position()};
    auto nested_type{type_expr()};

    if(!nested_type) {
      throw_syntax_error("Expected a type expression after *.");
    }

    // TODO: For now we always expect a typename.
    node = make_node<Pointer>(pos, std::move(nested_type));
  }

  return node;
}

auto TypeParser::type_id_native() -> NodePtr
{
  DBG_TRACE_FN(VERBOSE);
  NodePtr node{};

	// TODO: Parse and create node for primitive types.

  // const auto token{get_token()};
  // if(TokenType::IDENTIFIER)) {
  // }

  return node;
}

auto TypeParser::type_id() -> NodePtr
{
  DBG_TRACE_FN(VERBOSE);
  NodePtr node{};

  const auto token{get_token()};
  if(next_if(TokenType::IDENTIFIER)) {
    const auto pos{token.position()};
    const auto id{token.str()};

    DBG_TRACE_PRINT(INFO, "TypeName: ", id);
    node = make_node<TypeName>(pos, id);
  }

  return node;
}

auto TypeParser::type_expr() -> NodePtr
{
  DBG_TRACE_FN(VERBOSE);
  NodePtr node{};

  if(auto ptr{type_pointer()}; ptr) {
    node = std::move(ptr);
  } else if(auto ptr{type_id_native()}; ptr) {
    node = std::move(ptr);
  } else if(auto ptr{type_id()}; ptr) {
    node = std::move(ptr);
  }

  return node;
}
} // namespace parser::type
