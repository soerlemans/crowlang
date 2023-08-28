#ifndef CROW_AST_NODE_LIST_HPP
#define CROW_AST_NODE_LIST_HPP

// STL Includes:
#include <list>
#include <memory>

// Local Includes:
#include "node.hpp"
#include "node_interface.hpp"


namespace node {
/*! This is a list in the sense of a list of expressions or similar
 * Think a list of nodes separated by commas like function arguments
 * Or function call separated nodes
 */
class List : public NodeInterface, public std::list<NodePtr> {
  public:
  List() = default;

  // Must be defaulted, in order to create this function
  List(List&& t_list) = default;

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~List() override = default;
};
} // namespace node

#endif // CROW_AST_NODE_LIST_HPP
