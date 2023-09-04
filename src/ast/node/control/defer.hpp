#ifndef CROW_AST_NODE_CONTROL_DEFER_HPP
#define CROW_AST_NODE_CONTROL_DEFER_HPP

// Includes:
#include "../node_interface.hpp"

// Local Includes:
#include "control.hpp"


namespace ast::node::control {
class Defer : public NodeInterface {
  private:
  NodeListPtr m_body;

  public:
  Defer(NodeListPtr&& t_body);

  auto body() -> NodeListPtr&;

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~Defer() override = default;
};
} // namespace node::control

#endif // CROW_AST_NODE_CONTROL_DEFER_HPP
