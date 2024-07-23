#ifndef CROW_CROW_PARSER_PRATT_BINDING_MAPS_HPP
#define CROW_CROW_PARSER_PRATT_BINDING_MAPS_HPP

// Local Includes:
#include "binding_map.hpp"

namespace parser::pratt::binding {
// Parenthesis always have the highest precedence, so there is no need to assign
// them a binding power!

// Classes:
//! This class is a map of prefix operator binding powers.
class PrefixMap : public BindingMap {
  public:
  PrefixMap()
  {
    // Dereference:
    INSERT_BINDING(ASTERISK, 15, 15);

    // Unary operators:
    INSERT_BINDING(NOT, 14, 14);
    INSERT_BINDING(PLUS, 14, 14);
    INSERT_BINDING(MINUS, 14, 14);
  }
};

//! This class is a map of infix operator binding powers.
class InfixMap : public BindingMap {
  public:
  InfixMap()
  {
    // Member access:
    INSERT_BINDING(DOT, 15, 15);
    INSERT_BINDING(ARROW, 15, 15);

    // Factor:
    INSERT_BINDING(ASTERISK, 12, 13);     // Multiplication
    INSERT_BINDING(SLASH, 12, 13);        // Division
    INSERT_BINDING(PERCENT_SIGN, 12, 13); // Modulo

    // Arithmetic:
    INSERT_BINDING(PLUS, 10, 11);  // Addition
    INSERT_BINDING(MINUS, 10, 11); // Subtraction

    // Comparisons:
    INSERT_BINDING(LESS_THAN, 9, 9);
    INSERT_BINDING(LESS_THAN_EQUAL, 9, 9);
    INSERT_BINDING(EQUAL, 9, 9);
    INSERT_BINDING(NOT_EQUAL, 9, 9);
    INSERT_BINDING(GREATER_THAN, 9, 9);
    INSERT_BINDING(GREATER_THAN_EQUAL, 9, 9);

    // Logical
    INSERT_BINDING(AND, 7, 8);
    INSERT_BINDING(OR, 5, 6);

    // Ternary:
    INSERT_BINDING(QUESTION_MARK, 4, 3);

    // Assignments:
    INSERT_BINDING(MUL_ASSIGN, 2, 1);
    INSERT_BINDING(DIV_ASSIGN, 2, 1);
    INSERT_BINDING(MOD_ASSIGN, 2, 1);
    INSERT_BINDING(ADD_ASSIGN, 2, 1);
    INSERT_BINDING(SUB_ASSIGN, 2, 1);
    INSERT_BINDING(ASSIGNMENT, 2, 1);
  }
};
} // namespace parser::pratt::binding

#endif // CROW_CROW_PARSER_PRATT_BINDING_MAPS_HPP
