#ifndef CROW_AST_NODE_NODE_TRAITS_UNARY_OPERATOR_HPP
#define CROW_AST_NODE_NODE_TRAITS_UNARY_OPERATOR_HPP

// Includes:
#include "../node_interface.hpp"

// Local Includes:
#include "fdecl.hpp"


namespace ast::node::node_traits {
class UnaryOperator : virtual public NodeInterface {
  private:
  NodePtr m_left;

  public:
  explicit UnaryOperator(NodePtr&& t_left);

  virtual auto left() -> NodePtr&;

  auto accept(visitor::NodeVisitor* t_visitor) -> void override = 0;

  ~UnaryOperator() override = default;
};
} // namespace ast::node::node_traits

#endif // CROW_AST_NODE_NODE_TRAITS_UNARY_OPERATOR_HPP
