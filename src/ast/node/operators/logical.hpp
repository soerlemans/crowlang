#ifndef CROW_AST_NODE_OPERATORS_LOGICAL_HPP
#define CROW_AST_NODE_OPERATORS_LOGICAL_HPP

// Local Includes:
#include "binary_operator.hpp"
#include "operators.hpp"


namespace ast::node::operators {
// Not:
class Not : public UnaryOperator {
  public:
  Not(NodePtr&& t_left);

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~Not() override = default;
};

// And:
class And : public BinaryOperator {
  public:
  And(NodePtr&& t_left, NodePtr&& t_right);

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~And() override = default;
};

// Or:
class Or : public BinaryOperator {
  public:
  Or(NodePtr&& t_left, NodePtr&& t_right);

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~Or() override = default;
};
} // namespace ast::node::operators

#endif // CROW_AST_NODE_OPERATORS_LOGICAL_HPP
