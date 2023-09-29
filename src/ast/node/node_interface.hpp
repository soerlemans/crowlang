#ifndef CROW_AST_NODE_NODE_INTERFACE_HPP
#define CROW_AST_NODE_NODE_INTERFACE_HPP

// Includes:
#include "../../visitable/visitable.hpp"
#include "../visitor/node_visitor.hpp"

// Local Includes:
#include "fdecl.hpp"

namespace ast::node {
class NodeInterface : public visitable::Visitable<visitor::NodeVisitor> {
  public:
  virtual auto accept(visitor::NodeVisitor* t_visitor) -> visitable::Any = 0;

  virtual ~NodeInterface() = default;
};
} // namespace ast::node

#endif // CROW_AST_NODE_NODE_INTERFACE_HPP
