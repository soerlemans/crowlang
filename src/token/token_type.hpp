#ifndef NEWLANG_TOKEN_TOKEN_TYPE_HPP
#define NEWLANG_TOKEN_TOKEN_TYPE_HPP

// STL Includes:
#include <optional>

namespace token {
// forward declarations:
enum class TokenType;

// Aliases:
using TokenTypeOpt = std::optional<TokenType>;

// Enums:
enum class TokenType {
  // Variables:
  IDENTIFIER = 0,
  LET,
  CONST,

  // Package:
  PACKAGE,
  IMPORT,
  PRIVATE,
  PUBLIC,

  // Object oriented:
  STRUCT,
  INTERFACE,

  // Control statements:
  FUNCTION,
  SWITCH,
  CASE,
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

  ASSIGNMENT,

  // Comparison Tokens:
  LESS_THAN,
  LESS_THAN_EQUAL,

  EQUAL,
  NOT_EQUAL,

  GREATER_THAN,
  GREATER_THAN_EQUAL,

  // Logical:
  NOT,
  AND,
  OR,

  // Miscellaneous:
	ARROW,
  DOT,
  COMMA,
  QUESTION_MARK,
  COLON,
  SEMICOLON,

  // (these are often related to arithmetic expressions):
  PLUS,
  MINUS,
  ASTERISK,
  SLASH,
  PERCENT_SIGN,

  NEWLINE,
};
} // namespace token

#endif // NEWLANG_TOKEN_TOKEN_TYPE_HPP
