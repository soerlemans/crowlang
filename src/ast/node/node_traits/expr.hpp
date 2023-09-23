#ifndef CROW_AST_NODE_NODE_TRAITS_EXPR_HPP
#define CROW_AST_NODE_NODE_TRAITS_EXPR_HPP

// Includes:
#include "../node_interface.hpp"

// Local Includes:
#include "fdecl.hpp"


namespace ast::node::node_traits {
class Expr : virtual public NodeInterface {
  protected:
  NodePtr m_expr;

  public:
  Expr(NodePtr&& t_expr);

  virtual auto expr() -> NodePtr&;

  auto accept(visitor::NodeVisitor* t_visitor) -> void override = 0;

  ~Expr() override = default;
};
} // namespace ast::node::node_traits

#endif // CROW_AST_NODE_NODE_TRAITS_EXPR_HPP
