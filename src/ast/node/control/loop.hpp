#ifndef CROW_AST_NODE_CONTROL_LOOP_HPP
#define CROW_AST_NODE_CONTROL_LOOP_HPP

// Includes:
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"


namespace ast::node::control {
// Using Statements:
using container::TextPosition;
using node_traits::Body;
using node_traits::Condition;
using node_traits::Expr;
using node_traits::InitExpr;
using node_traits::NodePosition;

// Classes:
class Loop : public NodePosition,
             public InitExpr,
             public Condition,
             public Expr,
             public Body {
  public:
  Loop(TextPosition t_pos, NodePtr&& t_init, NodePtr&& t_condition,
       NodePtr&& t_expr, NodeListPtr&& t_body);

  MAKE_TRAITS_ARCHIVEABLE(Loop, NodePosition, InitExpr, Condition, Expr, Body)
  MAKE_VISITABLE(visitor::NodeVisitor);

  virtual ~Loop() = default;
};
} // namespace ast::node::control

// Cereal type registration:
REGISTER_ARCHIVEABLE_TYPE(ast::node::control, Loop);

#endif // CROW_AST_NODE_CONTROL_LOOP_HPP
