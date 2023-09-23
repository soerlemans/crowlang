#ifndef CROW_TOKEN_TOKEN_TYPE_HPP
#define CROW_TOKEN_TOKEN_TYPE_HPP

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
  CONST,
  LET,

  // Package:
  MODULE,
  IMPORT,
  USE,
  PRIVATE,
  PUBLIC,

  // Typing:
  STRUCT,
  INTERFACE,
	DEF,

  // Control statements:
  FUNCTION,
  MATCH,
  IF,
  ELSE,
  ELIF,
  LOOP,

  // Jump:
  BREAK,
  CONTINUE,
  DEFER,
  RETURN,

  // Literals:
  INTEGER,
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
  PLUS,
  MINUS,
  ASTERISK,
  SLASH,
  PERCENT_SIGN,

  INCREMENT,
  DECREMENT,

  // Assignment:
  MUL_ASSIGN,
  DIV_ASSIGN,
  MOD_ASSIGN,

  ADD_ASSIGN,
  SUB_ASSIGN,

  ASSIGNMENT,

  // Comparison Tokens:
  LESS_THAN,
  LESS_THAN_EQUAL,

  EQUAL,
  NOT_EQUAL,

  GREATER_THAN,
  GREATER_THAN_EQUAL,

  // Logical:
  TRUE,
  FALSE,

  NOT,
  AND,
  OR,

  // Miscellaneous:
  ARROW,
  DOT,
  COMMA,
  QUESTION_MARK,
  DOUBLE_COLON,
  COLON,
  SEMICOLON,

  NEWLINE
};
} // namespace token

#endif // CROW_TOKEN_TOKEN_TYPE_HPP
