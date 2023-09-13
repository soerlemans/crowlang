#ifndef EXPR_HPP
#define EXPR_HPP

// Includes:
#include "../node_interface.hpp"


namespace ast::node::node_traits {
class Expr : virtual public NodeInterface {
  protected:
  NodePtr m_expr;

  public:
  Expr(NodePtr&& t_expr);

  auto expr() -> NodePtr&;

  auto accept(visitor::NodeVisitor* t_visitor) -> void override = 0;

  ~Expr() override = default;
};
} // namespace ast::node::node_traits

#endif // EXPR_HPP
