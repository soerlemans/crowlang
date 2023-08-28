#ifndef CROW_AST_NODE_FUNCTIONS_FUNCTIONS_HPP
#define CROW_AST_NODE_FUNCTIONS_FUNCTIONS_HPP

// STL Includes:
#include <memory>


namespace ast::node::functions {
// Forward Declarations:
class Function;
class FunctionCall;

// Aliases:
using NodeFuncPtr = std::shared_ptr<Function>;
} // namespace node::functions

#endif // CROW_AST_NODE_FUNCTIONS_FUNCTIONS_HPP
