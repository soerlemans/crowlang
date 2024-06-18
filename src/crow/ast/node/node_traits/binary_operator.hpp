#ifndef CROW_CROW_AST_NODE_NODE_TRAITS_BINARY_OPERATOR_HPP
#define CROW_CROW_AST_NODE_NODE_TRAITS_BINARY_OPERATOR_HPP

// Local Includes:
#include "fdecl.hpp"
#include "unary_operator.hpp"

namespace ast::node::node_traits {
class BinaryOperator : public UnaryOperator {
  private:
  NodePtr m_right;

  public:
  explicit BinaryOperator(NodePtr&& t_left, NodePtr&& t_right);

  auto right() -> NodePtr&;

  AST_ARCHIVE_MAKE_TRAITS_ARCHIVEABLE(BinaryOperator, UnaryOperator)
  AST_VISITOR_VISITABLE_PURE_ACCEPT(visitor::NodeVisitor);

  virtual ~BinaryOperator() = default;
};
} // namespace ast::node::node_traits

// Cereal type registration:
REGISTER_ARCHIVEABLE_TYPE(ast::node::node_traits, BinaryOperator);

#endif // CROW_CROW_AST_NODE_NODE_TRAITS_BINARY_OPERATOR_HPP
