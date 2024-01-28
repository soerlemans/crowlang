#ifndef CROW_AST_NODE_NODE_TRAITS_BODY_HPP
#define CROW_AST_NODE_NODE_TRAITS_BODY_HPP

// Includes:
#include "../node_interface.hpp"

// Local Includes:
#include "fdecl.hpp"


namespace ast::node::node_traits {
class Body : virtual public NodeInterface {
  protected:
  NodeListPtr m_body;

  public:
  Body(NodeListPtr&& t_body);

  virtual auto body() -> NodeListPtr&;

	GIVE_ARCHIVE_ACCESS(Body);
  VISITABLE_PURE_ACCEPT(visitor::NodeVisitor);

  virtual ~Body() = default;
};
} // namespace ast::node::node_traits

#endif // CROW_AST_NODE_NODE_TRAITS_BODY_HPP
