#ifndef CROW_AST_NODE_FUNCTIONS_FDECL_HPP
#define CROW_AST_NODE_FUNCTIONS_FDECL_HPP

// STL Includes:
#include <memory>


namespace ast::node::functions {
// Forward Declarations:
class Function;
class FunctionCall;
class ReturnType;

// Aliases:
using NodeFnPtr = std::shared_ptr<Function>;
} // namespace ast::node::functions

#endif // CROW_AST_NODE_FUNCTIONS_FDECL_HPP
