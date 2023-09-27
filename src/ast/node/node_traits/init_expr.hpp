#ifndef CROW_AST_NODE_NODE_TRAITS_INIT_EXPR_HPP
#define CROW_AST_NODE_NODE_TRAITS_INIT_EXPR_HPP

// Includes:
#include "../node_interface.hpp"

// Local Includes:
#include "fdecl.hpp"


namespace ast::node::node_traits {
class InitExpr : virtual public NodeInterface {
  protected:
  NodePtr m_init;

  public:
  InitExpr(NodePtr&& t_init);

  virtual auto init_expr() -> NodePtr&;

  VISITABLE_PURE_ACCEPT(visitor::NodeVisitor);

  ~InitExpr() override = default;
};
} // namespace ast::node::node_traits


#endif // CROW_AST_NODE_NODE_TRAITS_INIT_EXPR_HPP
