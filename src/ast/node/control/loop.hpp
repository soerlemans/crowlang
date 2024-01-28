#ifndef CROW_AST_NODE_CONTROL_LOOP_HPP
#define CROW_AST_NODE_CONTROL_LOOP_HPP

// Includes:
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"


namespace ast::node::control {
// Aliases:
namespace nt = node_traits;
namespace ct = container;

// Classes:
class Loop : public nt::NodePosition,
             public nt::InitExpr,
             public nt::Condition,
             public nt::Expr,
             public nt::Body {
  public:
  Loop(ct::TextPosition t_pos, NodePtr&& t_init,
       NodePtr&& t_condition, NodePtr&& t_expr, NodeListPtr&& t_body);

  MAKE_VISITABLE(visitor::NodeVisitor);

  virtual ~Loop() = default;
};
} // namespace ast::node::control

#endif // CROW_AST_NODE_CONTROL_LOOP_HPP
