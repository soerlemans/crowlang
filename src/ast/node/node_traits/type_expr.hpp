#ifndef CROW_AST_NODE_NODE_TRAITS_TYPE_EXPR_HPP
#define CROW_AST_NODE_NODE_TRAITS_TYPE_EXPR_HPP

// Includes:
#include "../node_interface.hpp"


namespace ast::node::node_traits {
class TypeExpr : virtual public NodeInterface {
  protected:
  NodePtr m_type;

  public:
  TypeExpr(NodePtr&& t_type);

  auto type() -> NodePtr&;

  auto accept(visitor::NodeVisitor* t_visitor) -> void override = 0;

  ~TypeExpr() override = default;
};
} // namespace ast::node::node_traits

#endif // CROW_AST_NODE_NODE_TRAITS_TYPE_EXPR_HPP
