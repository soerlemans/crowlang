#ifndef CROW_CROW_AST_NODE_OPERATORS_ASSIGNMENT_HPP
#define CROW_CROW_AST_NODE_OPERATORS_ASSIGNMENT_HPP

// Includes:
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"

namespace ast::node::operators {
// Using Statements:
using container::TextPosition;
using node_traits::BinaryOperator;
using node_traits::NodePosition;
using node_traits::Op;

// Enums:
enum AssignmentOp {
  MULTIPLY = 0,
  DIVIDE,
  MODULO,

  ADD,
  SUBTRACT,

  REGULAR
};

// Classes:
class Assignment : public NodePosition,
                   public Op<AssignmentOp>,
                   public BinaryOperator {
  public:
  Assignment(TextPosition t_pos, AssignmentOp t_op, NodePtr&& t_left,
             NodePtr&& t_right);

  AST_ARCHIVE_MAKE_TRAITS_ARCHIVEABLE(Assignment, NodePosition,
                                      Op<AssignmentOp>, BinaryOperator)
  AST_VISITOR_MAKE_VISITABLE(visitor::NodeVisitor);

  virtual ~Assignment() = default;
};
} // namespace ast::node::operators

// Cereal type registration:
REGISTER_ARCHIVEABLE_TYPE(ast::node::operators, Assignment);
REGISTER_ARCHIVEABLE_TYPE(ast::node::node_traits,
                          Op<ast::node::operators::AssignmentOp>);

#endif // CROW_CROW_AST_NODE_OPERATORS_ASSIGNMENT_HPP
