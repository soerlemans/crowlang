#ifndef CROW_AST_NODE_CONTROL_RETURN_HPP
#define CROW_AST_NODE_CONTROL_RETURN_HPP

#include "../node_interface.hpp"

#include "control.hpp"


namespace node::control {
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
