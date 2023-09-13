#ifndef CROW_AST_NODE_FUNCTIONS_RETURN_TYPE_HPP
#define CROW_AST_NODE_FUNCTIONS_RETURN_TYPE_HPP

// Includes:
#include "../node_interface.hpp"

// Local Includes:
#include "fdecl.hpp"


namespace ast::node::functions {
class ReturnType : public NodeInterface {
  private:
  NodePtr m_type;

  public:
  ReturnType(NodePtr&& t_type);

  auto type() -> NodePtr&;

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~ReturnType() override = default;
};
} // namespace ast::node::functions

#endif // CROW_AST_NODE_FUNCTIONS_RETURN_TYPE_HPP
