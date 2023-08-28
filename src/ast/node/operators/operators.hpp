#ifndef CROW_AST_NODE_OPERATORS_OPERATORS_HPP
#define CROW_AST_NODE_OPERATORS_OPERATORS_HPP

#include "../node.hpp"

// All Operator classes are part of this namespace
// These forward declarations are also used by NodeVisitor
// To declare its overload functions for visit()
namespace node::operators {
// Abstract Base classes:
class UnaryOperator;
class BinaryOperator;

// UnaryOperator derived classes:
class UnaryPrefix;
class Grouping;
class Increment;
class Decrement;

// Logical:
class Not;

// BinaryOperator derived classes:
// Arithmetic:
class Arithmetic;

// String ops:
class StringConcatenation;

// Comparison:
class Comparison;

// ERE Match:
class Match;

// Array ops:
class Membership;

// Delete:
class Delete;

// Logical:
class And;
class Or;

// Assignment:
class Assignment;

// Trinary operator:
class Ternary;
} // namespace node::operators

#endif // CROW_AST_NODE_OPERATORS_OPERATORS_HPP
