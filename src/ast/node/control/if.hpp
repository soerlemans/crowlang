#ifndef CROW_AST_NODE_CONTROL_IF_HPP
#define CROW_AST_NODE_CONTROL_IF_HPP

// Includes:
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"


namespace ast::node::control {
// Aliases:
namespace nt = node_traits;

// Classes:
class If : public nt::Init, public nt::Condition {
  private:
  NodeListPtr m_then;
  NodeListPtr m_alt;

  public:
  If(NodePtr&& t_init, NodePtr&& t_condition, NodeListPtr&& t_then,
     NodeListPtr&& t_alt);

  auto then() -> NodeListPtr&;
  auto alt() -> NodeListPtr&;

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~If() override = default;
};
} // namespace ast::node::control

#endif // CROW_AST_NODE_CONTROL_IF_HPP
