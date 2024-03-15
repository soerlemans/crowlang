#ifndef CROW_AST_NODE_NODE_TRAITS_EXPR_HPP
#define CROW_AST_NODE_NODE_TRAITS_EXPR_HPP

// Includes:
#include "../include.hpp"

// Local Includes:
#include "fdecl.hpp"

namespace ast::node::node_traits {
class Expr : virtual public NodeInterface {
  private:
  NodePtr m_expr;

  public:
  Expr(NodePtr&& t_expr);

  auto expr() -> NodePtr&;

  AST_ARCHIVE_MAKE_ARCHIVEABLE(Expr)
  {
    t_archive(CEREAL_NVP(m_expr));
  }

  AST_VISITOR_VISITABLE_PURE_ACCEPT(visitor::NodeVisitor);

  virtual ~Expr() = default;
};
} // namespace ast::node::node_traits

// Cereal register type:
REGISTER_ARCHIVEABLE_TYPE(ast::node::node_traits, Expr);

#endif // CROW_AST_NODE_NODE_TRAITS_EXPR_HPP
