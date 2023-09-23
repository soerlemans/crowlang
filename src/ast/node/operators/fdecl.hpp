#ifndef CROW_AST_NODE_OPERATORS_FDECL_HPP
#define CROW_AST_NODE_OPERATORS_FDECL_HPP

// Forward Declarations:
namespace ast::node::operators {
// UnaryOperator derived classes:
class UnaryPrefix;
class Increment;
class Decrement;
class Not;

// BinaryOperator derived classes:
class Arithmetic;
class Comparison;
class And;
class Or;
class Assignment;

// Trinary operator:
class Ternary;
} // namespace node::operators

#endif // CROW_AST_NODE_OPERATORS_FDECL_HPP
