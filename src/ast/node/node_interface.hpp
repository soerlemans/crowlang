#ifndef CROW_AST_NODE_NODE_INTERFACE_HPP
#define CROW_AST_NODE_NODE_INTERFACE_HPP

// Includes:
#include "../visitor/node_visitor.hpp"


namespace ast::node {
class NodeInterface : public visitor::Visitable<visitor::NodeVisitor> {
  public:
  virtual auto accept(visitor::NodeVisitor* t_visitor) -> void = 0;

  virtual ~NodeInterface() = default;
};
} // namespace ast::node

#endif // CROW_AST_NODE_NODE_INTERFACE_HPP
