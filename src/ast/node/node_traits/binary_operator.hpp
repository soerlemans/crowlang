#ifndef CROW_AST_NODE_NODE_TRAITS_BINARY_OPERATOR_HPP
#define CROW_AST_NODE_NODE_TRAITS_BINARY_OPERATOR_HPP

// Local Includes:
#include "fdecl.hpp"
#include "unary_operator.hpp"


namespace ast::node::node_traits {
class BinaryOperator : public UnaryOperator {
  protected:
  NodePtr m_right;

  public:
  explicit BinaryOperator(NodePtr&& t_left, NodePtr&& t_right);

  virtual auto right() -> NodePtr&;

  VISITABLE_PURE_ACCEPT(visitor::NodeVisitor);

  virtual ~BinaryOperator() = default;
};
} // namespace ast::node::node_traits

#endif // CROW_AST_NODE_NODE_TRAITS_BINARY_OPERATOR_HPP
