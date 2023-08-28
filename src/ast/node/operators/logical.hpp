#ifndef CROW_AST_NODE_OPERATORS_LOGICAL_HPP
#define CROW_AST_NODE_OPERATORS_LOGICAL_HPP

#include "binary_operator.hpp"
#include "operators.hpp"


namespace node::operators {
// Not:
// Pay attention Not is not a BinaryOperator unlike the other Logical operators
// Like And and Or
class Not : public UnaryOperator {
  public:
  Not(NodePtr&& t_left);

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~Not() override = default;
};

// TODO: Create one class for And and Or
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
} // namespace node::operators

#endif // CROW_AST_NODE_OPERATORS_LOGICAL_HPP
