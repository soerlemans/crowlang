#ifndef CROW_AST_NODE_OPERATORS_BINARY_OPERATOR_HPP
#define CROW_AST_NODE_OPERATORS_BINARY_OPERATOR_HPP

// Local Includes:
#include "fdecl.hpp"
#include "unary_operator.hpp"


namespace ast::node::operators {
class BinaryOperator : public UnaryOperator {
  private:
  NodePtr m_right;

  public:
  explicit BinaryOperator(NodePtr&& t_left, NodePtr&& t_right);

  auto right() -> NodePtr&;

  auto accept(visitor::NodeVisitor* t_visitor) -> void override = 0;

  ~BinaryOperator() override = default;
};
} // namespace ast::node::operators

#endif // CROW_AST_NODE_OPERATORS_BINARY_OPERATOR_HPP
