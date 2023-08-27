#ifndef CROW_AST_NODE_HPP
#define CROW_AST_NODE_HPP

// STL Includes:
#include <memory>


namespace ast {
// Forward Declarations:
class NodeInterface;

// Aliases:
using NodePtr = std::shared_ptr<NodeInterface>;
} // namespace ast

#endif // CROW_AST_NODE_HPP
