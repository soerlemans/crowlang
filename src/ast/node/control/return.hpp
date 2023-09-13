#ifndef CROW_AST_NODE_CONTROL_RETURN_HPP
#define CROW_AST_NODE_CONTROL_RETURN_HPP

// Includes:
#include "../node_interface.hpp"

// Local Includes:
#include "fdecl.hpp"


namespace ast::node::control {
class Return : public NodeInterface {
  private:
  NodePtr m_expr;

  public:
  Return(NodePtr&& t_expr);

  auto expr() -> NodePtr&;

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~Return() override = default;
};
} // namespace node::control

#endif // CROW_AST_NODE_CONTROL_RETURN_HPP
