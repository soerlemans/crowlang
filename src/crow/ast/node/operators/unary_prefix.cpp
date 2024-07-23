#include "unary_prefix.hpp"

// STL Includes:
#include <exception>

// Macros:
#define MATCH(t_key, t_value) \
  case UnaryPrefixOp::t_key:  \
    str = t_value;            \
    break

namespace ast::node::operators {
// Using Declarations:
using token::TokenType;

// Methods:
UnaryPrefix::UnaryPrefix(const TokenType t_op, NodePtr&& t_left)
  : Op{token_type2unary_prefix_op(t_op)}, UnaryOperator{std::move(t_left)}
{}

UnaryPrefix::UnaryPrefix(const UnaryPrefixOp t_op, NodePtr&& t_left)
  : Op{t_op}, UnaryOperator{std::move(t_left)}
{}

auto UnaryPrefix::op2str() const -> std::string_view
{
  return unary_prefix_op2str(op());
}

// Functions:
auto token_type2unary_prefix_op(const TokenType t_type) -> UnaryPrefixOp
{
  UnaryPrefixOp op{UnaryPrefixOp::PLUS};

  if(t_type == TokenType::MINUS) {
    op = UnaryPrefixOp::MINUS;
  } else if(t_type != TokenType::PLUS) {
    // If we did not receive a convertible TokenType throw an exception.
    throw std::invalid_argument{"token_type2unary_prefix_op: TokenType could "
                                "not be converted to UnaryPrefixOp."};
  }

  return op;
}

auto unary_prefix_op2str(const UnaryPrefixOp t_op) -> std::string_view
{
  std::string_view str{};

  switch(t_op) {
    MATCH(PLUS, "+");
    MATCH(MINUS, "-");

    default:
      throw std::invalid_argument{
        "UnaryPrefixOp could not be converted to std::string_view."};
      break;
  }

  return str;
}
} // namespace ast::node::operators
