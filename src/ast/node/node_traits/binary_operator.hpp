#ifndef CROW_AST_NODE_NODE_TRAITS_BINARY_OPERATOR_HPP
#define CROW_AST_NODE_NODE_TRAITS_BINARY_OPERATOR_HPP

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

  MAKE_ARCHIVEABLE(BinaryOperator)
  {
    archive_traits<Archive, BinaryOperator, UnaryOperator>(t_archive, this);
  }

  VISITABLE_PURE_ACCEPT(visitor::NodeVisitor);

  virtual ~BinaryOperator() = default;
};
} // namespace ast::node::node_traits

// Cereal type registration:
REGISTER_ARCHIVEABLE_TYPE(ast::node::node_traits, BinaryOperator);

#endif // CROW_AST_NODE_NODE_TRAITS_BINARY_OPERATOR_HPP
