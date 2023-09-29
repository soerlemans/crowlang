#ifndef CROW_AST_NODE_FDECL_HPP
#define CROW_AST_NODE_FDECL_HPP

// STL Includes:
#include <memory>

// Includes:
// Forward declarations for all Node classes:
#include "control/fdecl.hpp"
#include "functions/fdecl.hpp"
#include "lvalue/fdecl.hpp"
#include "operators/fdecl.hpp"
#include "packaging/fdecl.hpp"
#include "rvalue/fdecl.hpp"
#include "typing/fdecl.hpp"

// Macros:
//! This macro allows you to include all node namespaces
#define NODE_USING_ALL_NAMESPACES()     \
  using namespace ast::node;            \
  using namespace ast::node::control;   \
  using namespace ast::node::functions; \
  using namespace ast::node::lvalue;    \
  using namespace ast::node::operators; \
  using namespace ast::node::packaging; \
  using namespace ast::node::rvalue;    \
  using namespace ast::node::typing;    \
  using namespace ast::node::node_traits;

namespace ast::node {
// Forward Declarations:
class NodeInterface;
class List;
class Nil;

// Aliases:
using NodePtr = std::shared_ptr<NodeInterface>;
using NodeListPtr = std::shared_ptr<List>;
} // namespace ast::node

#endif // CROW_AST_NODE_FDECL_HPP
