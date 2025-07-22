#include "assignment.hpp"

// Absolute Includes:
#include "lib/stdexcept/stdexcept.hpp"

// Macros:
#define MATCH(t_key, t_value) \
  case AssignmentOp::t_key:   \
    str = t_value;            \
    break

namespace ast::node::operators {
// Methods:
Assignment::Assignment(TextPosition t_pos, const AssignmentOp t_op,
                       NodePtr&& t_left, NodePtr&& t_right)
  : NodePosition{std::move(t_pos)},
    Op{t_op},
    BinaryOperator{std::move(t_left), std::move(t_right)}
{}

auto Assignment::op2str() const -> std::string_view
{
  return assignment_op2str(op());
}

// Functions:
auto assignment_op2str(const AssignmentOp t_op) -> std::string_view
{
  std::string_view str{};

  switch(t_op) {
    MATCH(MULTIPLY, "*=");
    MATCH(DIVIDE, "/=");
    MATCH(MODULO, "%=");

    MATCH(ADD, "+=");
    MATCH(SUBTRACT, "-=");

    MATCH(REGULAR, "=");

    default: {
      using lib::stdexcept::throw_invalid_argument;

      throw_invalid_argument(
        "AssignmentOp could not be converted to std::string_view.");
      break;
    }
  }

  return str;
}
} // namespace ast::node::operators
