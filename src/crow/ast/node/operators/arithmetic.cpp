#include "arithmetic.hpp"

// STL Includes:
#include <exception>

// Macros:
#define MATCH(t_key, t_value) \
  case ArithmeticOp::t_key:   \
    str = t_value;            \
    break

namespace ast::node::operators {
// Methods:
Arithmetic::Arithmetic(TextPosition t_pos, const ArithmeticOp t_op,
                       NodePtr&& t_left, NodePtr&& t_right)
  : NodePosition{std::move(t_pos)},
    Op{t_op},
    BinaryOperator{std::move(t_left), std::move(t_right)}
{}

auto Arithmetic::op2str() const -> std::string_view
{
  return arithmetic_op2str(op());
}

// Functions:
auto arithmetic_op2str(const ArithmeticOp t_op) -> std::string_view
{
  std::string_view str{};

  switch(t_op) {
    MATCH(POWER, "+");

    MATCH(MULTIPLY, "*");
    MATCH(DIVIDE, "/");
    MATCH(MODULO, "%");

    MATCH(ADD, "+");
    MATCH(SUBTRACT, "-");

    default:
      throw std::invalid_argument{
        "ArithmeticOp could not be converted to std::string_view."};
      break;
  }

  return str;
}
} // namespace ast::node::operators
