#ifndef CROW_CROW_AST_NODE_OPERATORS_LOGICAL_HPP
#define CROW_CROW_AST_NODE_OPERATORS_LOGICAL_HPP

// Includes:
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"

namespace ast::node::operators {
// Using Statements:
using container::TextPosition;
using node_traits::BinaryOperator;
using node_traits::NodePosition;
using node_traits::UnaryOperator;

// Not:
class Not : public NodePosition, public UnaryOperator {
  public:
  Not(TextPosition t_pos, NodePtr&& t_left);

  AST_ARCHIVE_MAKE_TRAITS_ARCHIVEABLE(Not, NodePosition, UnaryOperator)
  AST_VISITOR_MAKE_VISITABLE(visitor::NodeVisitor);

  virtual ~Not() = default;
};

// And:
class And : public NodePosition, public BinaryOperator {
  public:
  And(TextPosition t_pos, NodePtr&& t_left, NodePtr&& t_right);

  AST_ARCHIVE_MAKE_TRAITS_ARCHIVEABLE(And, NodePosition, BinaryOperator)
  AST_VISITOR_MAKE_VISITABLE(visitor::NodeVisitor);

  virtual ~And() = default;
};

// Or:
class Or : public NodePosition, public BinaryOperator {
  public:
  Or(TextPosition t_pos, NodePtr&& t_left, NodePtr&& t_right);

  AST_ARCHIVE_MAKE_TRAITS_ARCHIVEABLE(Or, NodePosition, BinaryOperator)
  AST_VISITOR_MAKE_VISITABLE(visitor::NodeVisitor);

  virtual ~Or() = default;
};
} // namespace ast::node::operators

REGISTER_ARCHIVEABLE_TYPE(ast::node::operators, Not);
REGISTER_ARCHIVEABLE_TYPE(ast::node::operators, And);
REGISTER_ARCHIVEABLE_TYPE(ast::node::operators, Or);

#endif // CROW_CROW_AST_NODE_OPERATORS_LOGICAL_HPP
