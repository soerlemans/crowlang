#ifndef CROW_AST_NODE_NODE_TRAITS_ARGS_HPP
#define CROW_AST_NODE_NODE_TRAITS_ARGS_HPP

// Includes:
#include "../include.hpp"

// Local Includes:
#include "fdecl.hpp"


namespace ast::node::node_traits {
class Args : virtual public NodeInterface {
  private:
  NodeListPtr m_args;

  public:
  Args(NodeListPtr&& t_args);

  auto args() -> NodeListPtr&;

  AST_ARCHIVE_MAKE_ARCHIVEABLE(Args)
  {
		t_archive(CEREAL_NVP(m_args));
	}

  AST_VISITOR_VISITABLE_PURE_ACCEPT(visitor::NodeVisitor);

  virtual ~Args() = default;
};
} // namespace ast::node::node_traits

// Cereal register type:
REGISTER_ARCHIVEABLE_TYPE(ast::node::node_traits, Args);

#endif // CROW_AST_NODE_NODE_TRAITS_ARGS_HPP
