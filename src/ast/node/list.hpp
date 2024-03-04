#ifndef CROW_AST_NODE_LIST_HPP
#define CROW_AST_NODE_LIST_HPP

// STL Includes:
#include <list>
#include <memory>

// Local Includes:
#include "fdecl.hpp"
#include "node_interface.hpp"


namespace ast::node {
/*!
 * This is a list in the sense of a list of expressions or similar
 * Think a list of nodes separated by commas like function arguments
 * Or function call separated nodes
 */
class List : public NodeInterface {
  private:
  // Aliases:
  using NodeList = std::list<NodePtr>;

  // Members:
  NodeList m_list;

  public:
  List() = default;
  List(List&& t_list) = default;

  auto begin() -> NodeList::iterator;
  auto end() -> NodeList::iterator;

  auto push_back(NodePtr&& t_ptr) -> void;

	auto empty() -> bool;

  template<typename Archive>
  auto serialize(Archive& t_archive) -> void
  {
    t_archive(m_list);
  }

  MAKE_VISITABLE(visitor::NodeVisitor);

  virtual ~List() = default;
};
} // namespace ast::node

// Cereal type registration:
REGISTER_ARCHIVEABLE_TYPE(ast::node, List);

#endif // CROW_AST_NODE_LIST_HPP
