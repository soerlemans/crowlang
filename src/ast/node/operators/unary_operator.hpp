#ifndef CROW_AST_NODE_OPERATORS_UNARY_OPERATOR_HPP
#define CROW_AST_NODE_OPERATORS_UNARY_OPERATOR_HPP

// Includes:
#include "../node_interface.hpp"

// Local Includes:
#include "operators.hpp"


namespace ast::node::operators {
class UnaryOperator : public NodeInterface {
  private:
  NodePtr m_left;

  public:
  explicit UnaryOperator(NodePtr&& t_left);

  auto left() -> NodePtr&;

  auto accept(visitor::NodeVisitor* t_visitor) -> void override = 0;

  ~UnaryOperator() override = default;
};
} // namespace ast::node::operators

#endif // CROW_AST_NODE_OPERATORS_UNARY_OPERATOR_HPP
