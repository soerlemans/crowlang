#ifndef CROW_CROW_PARSER_TYPE_TYPE_PARSER_HPP
#define CROW_CROW_PARSER_TYPE_TYPE_PARSER_HPP

// STL Includes:
#include <memory>
#include <unordered_map>
#include <utility>

// Absolute Includes:
#include "crow/parser/parser.hpp"
#include "lib/stdtypes.hpp"

namespace parser::type {
// Classes:
class TypeParser : public Parser {
  public:
  explicit TypeParser(ParserContextPtr t_ctx);

  virtual auto type_spec() -> NodePtr;

  virtual ~TypeParser() = default;
};
} // namespace parser::type

#endif // CROW_CROW_PARSER_TYPE_TYPE_PARSER_HPP
