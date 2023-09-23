#ifndef CROW_AST_NODE_NODE_TRAITS_THEN_HPP
#define CROW_AST_NODE_NODE_TRAITS_THEN_HPP

// Includes:
#include "../node_interface.hpp"

// Local Includes:
#include "fdecl.hpp"


namespace ast::node::node_traits {
class Then : virtual public NodeInterface {
  protected:
  NodePtr m_then;

  public:
  Then(NodePtr&& t_then);

  virtual auto then() -> NodePtr&;

  auto accept(visitor::NodeVisitor* t_visitor) -> void override = 0;

  ~Then() override = default;
};
} // namespace ast::node::node_traits

#endif // CROW_AST_NODE_NODE_TRAITS_THEN_HPP
