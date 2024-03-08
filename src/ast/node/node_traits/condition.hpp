#ifndef CROW_AST_NODE_NODE_TRAITS_CONDITION_HPP
#define CROW_AST_NODE_NODE_TRAITS_CONDITION_HPP

// Includes:
#include "../include.hpp"

// Local Includes:
#include "fdecl.hpp"


namespace ast::node::node_traits {
class Condition : virtual public NodeInterface {
  private:
  NodePtr m_condition;

  public:
  Condition(NodePtr&& t_condition);

  auto condition() -> NodePtr&;

  AST_ARCHIVE_MAKE_ARCHIVEABLE(Condition)
  {
		t_archive(CEREAL_NVP(m_condition));
	}

  AST_VISITOR_VISITABLE_PURE_ACCEPT(visitor::NodeVisitor);

  virtual ~Condition() = default;
};
} // namespace ast::node::node_traits

// Cereal register type:
REGISTER_ARCHIVEABLE_TYPE(ast::node::node_traits, Condition);

#endif // CROW_AST_NODE_NODE_TRAITS_CONDITION_HPP
