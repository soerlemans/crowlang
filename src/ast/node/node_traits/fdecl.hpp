#ifndef CROW_AST_NODE_NODE_TRAITS_FDECL_HPP
#define CROW_AST_NODE_NODE_TRAITS_FDECL_HPP


namespace ast::node::node_traits {
// Aliases:
namespace nt = node_traits;

// Forward Declarations:
class Body;
class Condition;
class DeclExpr;
class Expr;
class Identifier;
class InitExpr;
class NodePosition;
class Params;
class Type;
class Then;
class Alt;
class UnaryOperator;
class BinaryOperator;


template<typename T>
class Op;
} // namespace ast::node::node_traits

#endif // CROW_AST_NODE_NODE_TRAITS_FDECL_HPP
