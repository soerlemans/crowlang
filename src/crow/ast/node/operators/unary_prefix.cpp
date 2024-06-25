#include "unary_prefix.hpp"

// STL Includes:
#include <exception>

// Macros:
#define MATCH(t_key, t_value) \
  case UnaryPrefixOp::t_key:  \
    str = t_value;            \
    break

namespace ast::node::operators {
// Methods:
UnaryPrefix::UnaryPrefix(UnaryPrefixOp t_op, NodePtr&& t_left)
  : Op{t_op}, UnaryOperator{std::move(t_left)}
{}

auto UnaryPrefix::op2str() const -> std::string_view
{
  return unary_prefix_op2str(op());
}

// Functions:
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
