#ifndef CROW_AST_NODE_OPERATORS_ARITHMETIC_HPP
#define CROW_AST_NODE_OPERATORS_ARITHMETIC_HPP

// Includes:
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"


namespace ast::node::operators {
// Namespace aliases:
namespace nt = node_traits;
namespace ct = container;

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
class Arithmetic : public nt::NodePosition,
                   public nt::Op<ArithmeticOp>,
                   public nt::BinaryOperator {
  public:
  Arithmetic(ct::TextPosition t_pos, ArithmeticOp t_op, NodePtr&& t_left,
             NodePtr&& t_right);

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~Arithmetic() override = default;
};
} // namespace ast::node::operators

#endif
