#ifndef CROW_AST_NODE_OPERATORS_ARITHMETIC_HPP
#define CROW_AST_NODE_OPERATORS_ARITHMETIC_HPP

// Includes:
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"


namespace ast::node::operators {
// Namespace aliases:
using container::TextPosition;
using node_traits::BinaryOperator;
using node_traits::NodePosition;
using node_traits::Op;
using node_traits::typing::TypeData;

// Enums:
enum class ArithmeticOp {
  POWER = 0,

  MULTIPLY,
  DIVIDE,
  MODULO,

  ADD,
  SUBTRACT
};

// Classes:
class Arithmetic : public NodePosition,
                   public Op<ArithmeticOp>,
                   public BinaryOperator,
                   public TypeData {
  public:
  Arithmetic(TextPosition t_pos, ArithmeticOp t_op, NodePtr&& t_left,
             NodePtr&& t_right);

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~Arithmetic() override = default;
};
} // namespace ast::node::operators

#endif
