#ifndef CROW_AST_NODE_NODE_TRAITS_ALT_HPP
#define CROW_AST_NODE_NODE_TRAITS_ALT_HPP

// Includes:
#include "../include.hpp"

// Local Includes:
#include "fdecl.hpp"


namespace ast::node::node_traits {
class Alt : virtual public NodeInterface {
  private:
  NodePtr m_alt;

  public:
  Alt(NodePtr&& t_alt);

  virtual auto alt() -> NodePtr&;

  MAKE_ARCHIVEABLE(Alt)
  {
		t_archive(CEREAL_NVP(m_alt));
	}

  AST_VISITOR_VISITABLE_PURE_ACCEPT(visitor::NodeVisitor);

  virtual ~Alt() = default;
};
} // namespace ast::node::node_traits

// Cereal register type:
REGISTER_ARCHIVEABLE_TYPE(ast::node::node_traits, Alt);

#endif // CROW_AST_NODE_NODE_TRAITS_ALT_HPP
