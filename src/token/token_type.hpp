#ifndef NEWLANG_TOKEN_TOKEN_TYPE_HPP
#define NEWLANG_TOKEN_TOKEN_TYPE_HPP

namespace token {
enum class TokenType {
  IDENTIFIER = 0,
  LET,

  // Object oriented:
  STRUCT,
  INTERFACE,

  // Control statements:
  FUNCTION,
  SWITCH,
  IF,
  ELSE,
  LOOP,

  // Control flow:
  BREAK,
  CONTINUE,
  DEFER,
  RETURN,

  // Literals:
  INTEGER,
  HEX,
  FLOAT,
  STRING,

  // Braces:
  PAREN_OPEN,
  PAREN_CLOSE,

  ACCOLADE_OPEN,
  ACCOLADE_CLOSE,

  BRACE_OPEN,
  BRACE_CLOSE,

  // Arithmetic:
  INCREMENT,
  DECREMENT,

  // Assignment:
  MULTIPLY_ASSIGN,
  DIVIDE_ASSIGN,
  MODULO_ASSIGN,

  ADD_ASSIGN,
  SUBTRACT_ASSIGN,

  INIT_ASSIGN,
  ASSIGNMENT,

  // Comparison Tokens:
  LESS_THAN,
  LESS_THAN_EQUAL,

  EQUAL,
  NOT_EQUAL,

  GREATER_THAN,
  GREATER_THAN_EQUAL,

  // Logical Tokens:
  NOT,

  AND,
  OR,

  // Single symbols:
  COMMA,
  DOT,
  QUESTION_MARK,
  COLON,
  SEMICOLON,

  // Single symbols (usually used for arithmetic):
  PLUS,
  MINUS,
  ASTERISK,
  SLASH,
  PERCENT_SIGN,

  NEWLINE,
};
} // namespace token

#endif // NEWLANG_TOKEN_TOKEN_TYPE_HPP
