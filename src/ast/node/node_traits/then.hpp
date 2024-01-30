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

  MAKE_ARCHIVEABLE(Then)
  {
		t_archive(CEREAL_NVP(m_then));
	}

  VISITABLE_PURE_ACCEPT(visitor::NodeVisitor);

  virtual ~Then() = default;
};
} // namespace ast::node::node_traits

// Cereal register type:
REGISTER_ARCHIVEABLE_TYPE(ast::node::node_traits, Then);

#endif // CROW_AST_NODE_NODE_TRAITS_THEN_HPP
