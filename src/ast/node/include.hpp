#ifndef CROW_AST_NODE_INCLUDE_HPP
#define CROW_AST_NODE_INCLUDE_HPP

/*! This header is made to include the headers of all classes that inherit from
 * Node, this to
 */

// Top level:
#include "fdecl.hpp"
#include "list.hpp"
#include "nil.hpp"
#include "node_interface.hpp"

// Control Statements:
#include "control/break.hpp"
#include "control/continue.hpp"
#include "control/defer.hpp"
#include "control/if.hpp"
#include "control/loop.hpp"
#include "control/return.hpp"

// Functions:
#include "functions/function.hpp"
#include "functions/function_call.hpp"
#include "functions/functions.hpp"

// Lvalue:
#include "lvalue/let.hpp"
#include "lvalue/lvalue.hpp"
#include "lvalue/variable.hpp"

// Operators:
#include "operators/arithmetic.hpp"
#include "operators/assignment.hpp"
#include "operators/comparison.hpp"
#include "operators/decrement.hpp"
#include "operators/increment.hpp"
#include "operators/logical.hpp"
#include "operators/operators.hpp"
#include "operators/ternary.hpp"
#include "operators/unary_prefix.hpp"

// Packaging:
#include "packaging/import.hpp"
#include "packaging/package.hpp"

// Rvalue:
#include "rvalue/literal.hpp"
#include "rvalue/rvalue.hpp"

// Typing:
#include "typing/impl.hpp"
#include "typing/interface.hpp"
#include "typing/struct.hpp"

#endif // CROW_AST_NODE_INCLUDE_HPP
