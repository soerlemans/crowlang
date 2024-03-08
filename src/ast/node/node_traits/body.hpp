#ifndef CROW_AST_NODE_NODE_TRAITS_BODY_HPP
#define CROW_AST_NODE_NODE_TRAITS_BODY_HPP

// Includes:
#include "../include.hpp"

// Local Includes:
#include "fdecl.hpp"


namespace ast::node::node_traits {
class Body : virtual public NodeInterface {
  private:
  NodeListPtr m_body;

  public:
  Body(NodeListPtr&& t_body);

  auto body() -> NodeListPtr&;

  MAKE_ARCHIVEABLE(Body)
  {
		t_archive(CEREAL_NVP(m_body));
	}

  AST_VISITOR_VISITABLE_PURE_ACCEPT(visitor::NodeVisitor);

  virtual ~Body() = default;
};
} // namespace ast::node::node_traits

// Cereal register type:
REGISTER_ARCHIVEABLE_TYPE(ast::node::node_traits, Body);

#endif // CROW_AST_NODE_NODE_TRAITS_BODY_HPP
