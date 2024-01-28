#ifndef CROW_AST_NODE_NIL_HPP
#define CROW_AST_NODE_NIL_HPP

// Local Includes:
#include "fdecl.hpp"
#include "node_interface.hpp"


namespace ast::node {
class Nil : public NodeInterface {
  public:
  MAKE_VISITABLE(visitor::NodeVisitor);

  virtual ~Nil() = default;
};
} // namespace ast::node

#endif // CROW_AST_NODE_NIL_HPP
