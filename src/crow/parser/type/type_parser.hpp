#ifndef CROW_CROW_PARSER_PRATT_PRATT_PARSER_HPP
#define CROW_CROW_PARSER_PRATT_PRATT_PARSER_HPP

// STL Includes:
#include <memory>
#include <unordered_map>
#include <utility>

// Absolute Includes:
#include "crow/parser/parser.hpp"
#include "lib/stdtypes.hpp"

namespace parser::type {
// Forward Declarations:
class TypeParser;

// Using Statements:
using TypeParserPtr = std::unique_ptr<TypeParser>;

// Classes:
class TypeParser : public Parser {
  public:
  TypeParser(TokenStream&& t_token_stream);

  virtual auto type_spec() -> NodePtr;

  virtual ~TypeParser() = default;
};
} // namespace parser::pratt

#endif // CROW_CROW_PARSER_PRATT_PRATT_PARSER_HPP
