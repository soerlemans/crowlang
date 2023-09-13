#ifndef CROW_AST_NODE_NODE_TRAITS_BODY_HPP
#define CROW_AST_NODE_NODE_TRAITS_BODY_HPP

// Includes:
#include "../node_interface.hpp"


namespace ast::node::node_traits {
class Body : public NodeInterface {
  protected:
	NodeListPtr m_body;

  public:
  Body(NodeListPtr&& t_body);

  auto body() -> NodeListPtr&;

  auto accept(visitor::NodeVisitor* t_visitor) -> void override = 0;

  ~Body() override = default;
};
} // namespace ast::node::node_triats

#endif // CROW_AST_NODE_NODE_TRAITS_BODY_HPP
