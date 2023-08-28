#ifndef FDECL_HPP
#define FDECL_HPP

// Local Includes:
// Forward declarations all Node classes:
#include "control/control.hpp"
#include "functions/functions.hpp"
#include "lvalue/lvalue.hpp"
#include "operators/operators.hpp"
#include "rvalue/rvalue.hpp"

namespace ast::node {
// Forward Declarations:
class NodeInterface;
class List;
class Nil;

// Aliases:
using NodePtr = std::shared_ptr<NodeInterface>;
using NodeListPtr = std::shared_ptr<List>;
} // namespace ast::node

#endif // FDECL_HPP
