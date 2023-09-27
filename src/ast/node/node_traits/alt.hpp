#ifndef CROW_AST_NODE_NODE_TRAITS_ALT_HPP
#define CROW_AST_NODE_NODE_TRAITS_ALT_HPP

// Includes:
#include "../node_interface.hpp"

// Local Includes:
#include "fdecl.hpp"


namespace ast::node::node_traits {
class Alt : virtual public NodeInterface {
  protected:
  NodePtr m_alt;

  public:
  Alt(NodePtr&& t_alt);

  virtual auto alt() -> NodePtr&;

  VISITABLE_PURE_ACCEPT(visitor::NodeVisitor);

  ~Alt() override = default;
};
} // namespace ast::node::node_traits

#endif // CROW_AST_NODE_NODE_TRAITS_ALT_HPP
