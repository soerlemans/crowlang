#ifndef LOOP_HPP
#define LOOP_HPP

// Includes:
#include "../node_interface.hpp"

// Local Includes:
#include "control.hpp"


namespace ast::node::control {
class Loop : public NodeInterface {
  private:
  NodePtr m_init;
  NodePtr m_condition;
  NodePtr m_expr;

  NodeListPtr m_body;

  public:
  Loop(NodePtr&& t_init, NodePtr&& t_condition, NodePtr&& t_expr,
       NodeListPtr&& t_body);

  auto init() -> NodePtr&;
  auto condition() -> NodePtr&;
  auto expr() -> NodePtr&;

  auto body() -> NodeListPtr&;

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~Loop() override = default;
};
} // namespace ast::node::control

#endif // LOOP_HPP
