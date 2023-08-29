#ifndef CROW_AST_NODE_MAP_HPP
#define CROW_AST_NODE_MAP_HPP

// STL Includes:
#include <map>

// Local Includes:
#include "node.hpp"
#include "node_interface.hpp"


namespace ast::node {
template<typename Key, typename Val>
class Map : public ast::node::NodeInterface, public std::map<Key, Val> {
  public:
  Map() = default;

  // Must be defaulted, in order to create this function
  Map(Map&& t_map) = default;

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~Map() override = default;
};
} // namespace ast::node

#endif // CROW_AST_NODE_MAP_HPP
