#ifndef CROW_CROW_AST_NODE_NODE_TRAITS_FDECL_HPP
#define CROW_CROW_AST_NODE_NODE_TRAITS_FDECL_HPP

// Local Includes:
// Forward declarations for all Node classes:
#include "typing/fdecl.hpp"

namespace ast::node::node_traits {
// Forward Declarations:
class Args;
class Body;
class Condition;
class DeclExpr;
class Expr;
class Identifier;
class InitExpr;
class NodePosition;
class Params;
class TypeAnnotation;
class Then;
class Alt;
class UnaryOperator;
class BinaryOperator;

template<typename T>
class Op;
} // namespace ast::node::node_traits

#endif // CROW_CROW_AST_NODE_NODE_TRAITS_FDECL_HPP
