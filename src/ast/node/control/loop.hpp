#ifndef CROW_AST_NODE_CONTROL_LOOP_HPP
#define CROW_AST_NODE_CONTROL_LOOP_HPP

// Includes:
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"


namespace ast::node::control {
// Aliases:
namespace nt = node_traits;

// Classes:
class Loop : public nt::InitExpr,
             public nt::Condition,
             public nt::Body,
             public nt::Expr {
  public:
  Loop(NodePtr&& t_init, NodePtr&& t_condition, NodePtr&& t_expr,
       NodeListPtr&& t_body);

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~Loop() override = default;
};
} // namespace ast::node::control

#endif // CROW_AST_NODE_CONTROL_LOOP_HPP
