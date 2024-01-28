#ifndef CROW_AST_NODE_OPERATORS_LOGICAL_HPP
#define CROW_AST_NODE_OPERATORS_LOGICAL_HPP

// Includes:
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"


namespace ast::node::operators {
// Namespace aliases:
namespace nt = node_traits;
namespace ct = container;

// Not:
class Not : public nt::NodePosition, public nt::UnaryOperator {
  public:
  Not(ct::TextPosition t_pos, NodePtr&& t_left);

  MAKE_VISITABLE(visitor::NodeVisitor);

  virtual ~Not() = default;
};

// And:
class And : public nt::NodePosition, public nt::BinaryOperator {
  public:
  And(ct::TextPosition t_pos, NodePtr&& t_left, NodePtr&& t_right);

  MAKE_VISITABLE(visitor::NodeVisitor);

  virtual ~And() = default;
};

// Or:
class Or : public nt::NodePosition, public nt::BinaryOperator {
  public:
  Or(ct::TextPosition t_pos, NodePtr&& t_left, NodePtr&& t_right);

  MAKE_VISITABLE(visitor::NodeVisitor);

  virtual ~Or() = default;
};
} // namespace ast::node::operators

#endif // CROW_AST_NODE_OPERATORS_LOGICAL_HPP
