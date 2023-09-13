#ifndef CROW_AST_NODE_CONTROL_IF_HPP
#define CROW_AST_NODE_CONTROL_IF_HPP

// Includes:
#include "../node_interface.hpp"

// Local Includes:
#include "fdecl.hpp"


namespace ast::node::control {
class If : public NodeInterface {
  private:
  NodePtr m_init;
  NodePtr m_condition;
  NodeListPtr m_then;
  NodeListPtr m_alt;

  public:
  If(NodePtr&& t_init, NodePtr&& t_condition, NodeListPtr&& t_then,
     NodeListPtr&& t_alt);

  auto init() -> NodePtr&;
  auto condition() -> NodePtr&;
  auto then() -> NodeListPtr&;
  auto alt() -> NodeListPtr&;

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~If() override = default;
};
} // namespace ast::node::control

#endif // CROW_AST_NODE_CONTROL_IF_HPP
