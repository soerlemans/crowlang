#include "comparison.hpp"

// STL Includes:
#include <exception>

// Macros:
#define MATCH(t_key, t_value) \
  case ComparisonOp::t_key:   \
    str = t_value;            \
    break

namespace ast::node::operators {
// Methods:
Comparison::Comparison(TextPosition t_pos, ComparisonOp t_op, NodePtr&& t_left,
                       NodePtr&& t_right)
  : NodePosition{std::move(t_pos)},
    Op{t_op},
    BinaryOperator{std::move(t_left), std::move(t_right)}
{}

auto Comparison::op2str() const -> std::string_view
{
  return comparison_op2str(op());
}

// Functions:
auto comparison_op2str(const ComparisonOp t_op) -> std::string_view
{
  std::string_view str{};

  switch(t_op) {
    MATCH(LESS_THAN, "<");
    MATCH(LESS_THAN_EQUAL, "<=");

    MATCH(EQUAL, "==");
    MATCH(NOT_EQUAL, "!=");

    MATCH(GREATER_THAN, ">");
    MATCH(GREATER_THAN_EQUAL, ">=");

    default:
      throw std::invalid_argument{
        "ComparisonOp could not be converted to std::string_view."};
      break;
  }

  return str;
}
} // namespace ast::node::operators
