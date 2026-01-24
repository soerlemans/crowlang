#ifndef ACRIS_ACRIS_AST_NODE_RVALUE_FDECL_HPP
#define ACRIS_ACRIS_AST_NODE_RVALUE_FDECL_HPP

// STL Includes:
#include <memory>
#include <string>
#include <vector>

// Absolute Includes:
#include "acris/ast/node/fdecl.hpp"
#include "lib/stdtypes.hpp"

namespace ast::node {
// Forward Declarations:
class List;

// Aliases:
using NodeListPtr = std::shared_ptr<List>;
} // namespace ast::node

namespace ast::node::rvalue {
// Forward Declarations:
template<typename T>
class Literal;

// Aliases:
using Integer = Literal<i64>;                      // let val = 10.
using Float = Literal<f64>;                        // let val = 10.0.
using Char = Literal<char>;                        // let val = '\0'.
using String = Literal<std::string>;               // let val = "hello".
using Boolean = Literal<bool>;                     // let val = true.
using ArrayExpr = Literal<ast::node::NodeListPtr>; // let val = [1, 2, 3].
} // namespace ast::node::rvalue

#endif // ACRIS_ACRIS_AST_NODE_RVALUE_FDECL_HPP
