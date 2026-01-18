#ifndef ACRIS_ACRIS_TOKEN_TOKEN_TYPE_HPP
#define ACRIS_ACRIS_TOKEN_TOKEN_TYPE_HPP

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
  VAR,

  // Package:
  MODULE,
  IMPORT,
  EXPORT,

  // Meta:
  HASH, // Used for preprocessor directives.
  ATTRIBUTE_OPEN,
  ATTRIBUTE_CLOSE,

  DECLARE,
  MACRO,
  CONST,

  // User Types:
  ALIAS,
  ENUM,
  STRUCT,
  SELF,

  PROTO,

  // Control statements:
  FUNCTION,
  METHOD,
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
  CHAR,
  STRING,

  // Braces:
  PAREN_OPEN,
  PAREN_CLOSE,

  ACCOLADE_OPEN,
  ACCOLADE_CLOSE,

  BRACKET_OPEN,
  BRACKET_CLOSE,

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

  // Comments:
  LINE_COMMENT,  // Starts with "//".
  BLOCK_COMMENT, // Starts with "/*" ends with "*/", may span multiple lines.

  // Miscellaneous:
  ARROW,
  DOT,
  COMMA,
  QUESTION_MARK,
  DOUBLE_COLON,
  COLON,
  SEMICOLON,
  AMPERSAND,

  NEWLINE
};
} // namespace token

#endif // ACRIS_ACRIS_TOKEN_TOKEN_TYPE_HPP
