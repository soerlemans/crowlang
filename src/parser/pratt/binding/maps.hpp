#ifndef AWX_PARSER_PRATT_BINDING_MAPS_HPP
#define AWX_PARSER_PRATT_BINDING_MAPS_HPP

// Local Includes:
#include "binding_map.hpp"


namespace parser::pratt::binding {
// TODO: Figure out how to deal with parenthesis
// BINDING_POWER(GROUPING, 25, 25);

// Classes:
//! This class is a map of prefix operator binding powers
class PrefixMap : public BindingMap {
  public:
  PrefixMap()
  {
    using namespace token;

    // Field reference:
    INSERT_BINDING(DOLLAR_SIGN, 24, 24);

    // Precrement:
    INSERT_BINDING(INCREMENT, 22, 22);
    INSERT_BINDING(DECREMENT, 22, 22);

    // Unary operators:
    INSERT_BINDING(NOT, 19, 19);
    INSERT_BINDING(PLUS, 19, 19);
    INSERT_BINDING(MINUS, 19, 19);
  }
};

//! This class is a map of prefix operator binding powers
class InfixMap : public BindingMap {
  public:
  InfixMap()
  {
    // Exponentation:
    INSERT_BINDING(CARET, 21, 20);

    // Factor:
    INSERT_BINDING(ASTERISK, 17, 18);     // Multiplication
    INSERT_BINDING(SLASH, 17, 18);        // Division
    INSERT_BINDING(PERCENT_SIGN, 17, 18); // Modulo

    // Arithmetic:
    INSERT_BINDING(PLUS, 15, 16);  // Addition
    INSERT_BINDING(MINUS, 15, 16); // Subtraction

    // Comparisons:
    INSERT_BINDING(LESS_THAN, 12, 12);
    INSERT_BINDING(LESS_THAN_EQUAL, 12, 12);
    INSERT_BINDING(EQUAL, 12, 12);
    INSERT_BINDING(NOT_EQUAL, 12, 12);
    INSERT_BINDING(GREATER_THAN, 12, 12);
    INSERT_BINDING(GREATER_THAN_EQUAL, 12, 12);

    // Extended regular expression matching:
    INSERT_BINDING(ERE_MATCH, 11, 11);
    INSERT_BINDING(ERE_NO_MATCH, 11, 11);

    // Array membership:
    INSERT_BINDING(IN, 9, 10);

    // Logical
    INSERT_BINDING(AND, 7, 8);
    INSERT_BINDING(OR, 5, 6);

    // Ternary:
    INSERT_BINDING(QUESTION_MARK, 4, 3);

    // Assignments:
    INSERT_BINDING(POWER_ASSIGNMENT, 2, 1);
    INSERT_BINDING(MULTIPLY_ASSIGNMENT, 2, 1);
    INSERT_BINDING(DIVIDE_ASSIGNMENT, 2, 1);
    INSERT_BINDING(MODULO_ASSIGNMENT, 2, 1);
    INSERT_BINDING(ADD_ASSIGNMENT, 2, 1);
    INSERT_BINDING(SUBTRACT_ASSIGNMENT, 2, 1);
    INSERT_BINDING(ASSIGNMENT, 2, 1);
  }

  auto string_concat() -> BindingPower
  {
    // No infix operator means that we are dealing with a string concatenation
    return {13, 14};
  }
};

//! This class is a map of prefix operator binding powers
class PostfixMap : public BindingMap {
  public:
  PostfixMap()
  {
    // Postcrement:
    INSERT_BINDING(INCREMENT, 23, 23);
    INSERT_BINDING(DECREMENT, 23, 23);
  }
};

} // namespace parser::pratt::binding

#endif // AWX_PARSER_PRATT_BINDING_MAPS_HPP
