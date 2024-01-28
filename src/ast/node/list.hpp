#ifndef CROW_AST_NODE_LIST_HPP
#define CROW_AST_NODE_LIST_HPP

// STL Includes:
#include <list>
#include <memory>

// Local Includes:
#include "fdecl.hpp"
#include "node_interface.hpp"


namespace ast::node {
/*! This is a list in the sense of a list of expressions or similar
 * Think a list of nodes separated by commas like function arguments
 * Or function call separated nodes
 */
class List : public NodeInterface, public std::list<NodePtr> {
  public:
  List() = default;

  // Must be defaulted, in order to create this function
  List(List&& t_list) = default;

  // template<typename Archive>
  // auto serialize(Archive& t_archive) -> void
  // {
	// 	const auto list{dynamic_cast<std::list<NodePtr>*>(this)};

  //   t_archive(*list);
  // }

  MAKE_VISITABLE(visitor::NodeVisitor);

  virtual ~List() = default;
};
} // namespace ast::node

// Cereal type registration:
// REGISTER_ARCHIVEABLE_TYPE(ast::node, List);

#endif // CROW_AST_NODE_LIST_HPP
