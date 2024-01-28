#ifndef CROW_AST_NODE_OPERATORS_ASSIGNMENT_HPP
#define CROW_AST_NODE_OPERATORS_ASSIGNMENT_HPP

// Includes:
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"


namespace ast::node::operators {
// Namespace aliases:
namespace nt = node_traits;
namespace ct = container;

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
class Assignment : public nt::NodePosition,
                   public nt::Op<AssignmentOp>,
                   public nt::BinaryOperator {
  public:
  Assignment(ct::TextPosition t_pos, AssignmentOp t_op, NodePtr&& t_left,
             NodePtr&& t_right);

  MAKE_VISITABLE(visitor::NodeVisitor);

  virtual ~Assignment() = default;
};
} // namespace ast::node::operators

#endif // CROW_AST_NODE_OPERATORS_ASSIGNMENT_HPP
