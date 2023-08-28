#ifndef CROW_AST_NODE_OPERATORS_ARITHMETIC_HPP
#define CROW_AST_NODE_OPERATORS_ARITHMETIC_HPP

#include "binary_operator.hpp"
#include "operators.hpp"


namespace node::operators {
enum class ArithmeticOp {
  POWER = 0,

  MULTIPLY,
  DIVIDE,
  MODULO,

  ADD,
  SUBTRACT
};

class Arithmetic : public BinaryOperator {
  private:
  ArithmeticOp m_op;

  public:
  Arithmetic(ArithmeticOp t_op, NodePtr&& t_left, NodePtr&& t_right);

  auto op() -> ArithmeticOp;

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~Arithmetic() override = default;
};
} // namespace node::operators

#endif
