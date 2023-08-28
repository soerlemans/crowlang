#ifndef CROW_AST_NODE_CONTROL_IF_HPP
#define CROW_AST_NODE_CONTROL_IF_HPP

#include "../node_interface.hpp"

#include "control.hpp"


namespace node::control {
class If : public NodeInterface {
  private:
  NodePtr m_condition;
  NodePtr m_then;
  NodePtr m_alt;

  public:
  If(NodePtr&& t_condition, NodePtr&& t_then);
  If(NodePtr&& t_condition, NodePtr&& t_then, NodePtr&& t_alt);

  auto condition() -> NodePtr&;
  auto then() -> NodePtr&;
  auto alt() -> NodePtr&;

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~If() override = default;
};
} // namespace node::control

#endif // CROW_AST_NODE_CONTROL_IF_HPP
