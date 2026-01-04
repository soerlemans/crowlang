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
TypeParser::TypeParser(TokenStream&& t_token_stream)
  : Parser{std::move(t_token_stream)}
{}

auto TypeParser::type_spec() -> NodePtr
{
  return {nullptr};
}

} // namespace parser::type
