#ifndef CROW_AST_NODE_NODE_TRAITS_INIT_EXPR_HPP
#define CROW_AST_NODE_NODE_TRAITS_INIT_EXPR_HPP

// Includes:
#include "../include.hpp"

// Local Includes:
#include "fdecl.hpp"


namespace ast::node::node_traits {
class InitExpr : virtual public NodeInterface {
  private:
  NodePtr m_init;

  public:
  InitExpr() = default;
  InitExpr(NodePtr&& t_init);

  auto init_expr() -> NodePtr&;

  template<typename Archive>
  auto serialize(Archive& t_archive) -> void
  {
    t_archive(m_init);
  }

  VISITABLE_PURE_ACCEPT(visitor::NodeVisitor);

  virtual ~InitExpr() = default;
};
} // namespace ast::node::node_traits

// Cereal type registration:
REGISTER_ARCHIVEABLE_TYPE(ast::node::node_traits, InitExpr);

#endif // CROW_AST_NODE_NODE_TRAITS_INIT_EXPR_HPP
