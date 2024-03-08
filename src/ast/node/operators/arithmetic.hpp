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

  AST_ARCHIVE_MAKE_TRAITS_ARCHIVEABLE(Arithmetic, NodePosition, Op<ArithmeticOp>,
                          BinaryOperator)
  AST_VISITOR_MAKE_VISITABLE(visitor::NodeVisitor);

  virtual ~Arithmetic() = default;
};
} // namespace ast::node::operators

// Cereal type registration:
REGISTER_ARCHIVEABLE_TYPE(ast::node::operators, Arithmetic);
REGISTER_ARCHIVEABLE_TYPE(ast::node::node_traits,
                          Op<ast::node::operators::ArithmeticOp>);

#endif // CROW_AST_NODE_OPERATORS_ARITHMETIC_HPP
