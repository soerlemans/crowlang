#ifndef CROW_AST_NODE_NODE_HPP
#define CROW_AST_NODE_NODE_HPP

// STL Includes:
#include <memory>

namespace ast::node {
// Forward Declarations:
class NodeInterface;
class List;
class Nil;

// template<typename Key, typename Val>
// class Map<Key, Val>;


// Aliases:
using NodePtr = std::shared_ptr<NodeInterface>;
using NodeListPtr = std::shared_ptr<List>;
} // namespace ast::node

#endif // CROW_AST_NODE_NODE_HPP
