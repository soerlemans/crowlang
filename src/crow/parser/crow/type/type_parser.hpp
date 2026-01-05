#ifndef CROW_CROW_PARSER_CROW_TYPE_TYPE_PARSER_HPP
#define CROW_CROW_PARSER_CROW_TYPE_TYPE_PARSER_HPP

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

  virtual auto type_name() -> NodePtr;
  virtual auto type_pointer() -> NodePtr;

  virtual auto type_expr() -> NodePtr;

  virtual ~TypeParser() = default;
};
} // namespace parser::type

#endif // CROW_CROW_PARSER_CROW_TYPE_TYPE_PARSER_HPP
