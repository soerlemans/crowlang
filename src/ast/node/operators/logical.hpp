#ifndef CROW_AST_NODE_OPERATORS_LOGICAL_HPP
#define CROW_AST_NODE_OPERATORS_LOGICAL_HPP

// Includes:
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"


namespace ast::node::operators {
// Namespace aliases:
namespace nt = node_traits;

// Not:
class Not : public nt::UnaryOperator {
  public:
  Not(NodePtr&& t_left);

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~Not() override = default;
};

// And:
class And : public nt::BinaryOperator {
  public:
  And(NodePtr&& t_left, NodePtr&& t_right);

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~And() override = default;
};

// Or:
class Or : public nt::BinaryOperator {
  public:
  Or(NodePtr&& t_left, NodePtr&& t_right);

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~Or() override = default;
};
} // namespace ast::node::operators

#endif // CROW_AST_NODE_OPERATORS_LOGICAL_HPP
