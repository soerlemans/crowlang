#ifndef NEWLANG_TOKEN_RESERVED_RESERVED_HPP
#define NEWLANG_TOKEN_RESERVED_RESERVED_HPP

// STL Includes:
#include <array>
#include <string_view>
#include <type_traits>

// Local Includes:
#include "../symbol.hpp"


namespace token::reserved {
// Macros:
// Do not use these macros outside of this file!
#define DEFINE_RESERVED(name, id, token) \
  constexpr Symbol name        \
  {                                      \
    id, TokenType::token                 \
  }

// clang-format off
// Language reserved keywords
namespace keywords {
  DEFINE_RESERVED(g_function, "fn", FUNCTION);
  DEFINE_RESERVED(g_return,   "return",   RETURN);

  DEFINE_RESERVED(g_if,   "if",   IF);
  DEFINE_RESERVED(g_else, "else", ELSE);

  DEFINE_RESERVED(g_do,    "do",    DO);
  DEFINE_RESERVED(g_while, "while", WHILE);
  DEFINE_RESERVED(g_for,   "for",   FOR);
  DEFINE_RESERVED(g_in,    "in",    IN);

  DEFINE_RESERVED(g_break,    "break",    BREAK);
  DEFINE_RESERVED(g_continue, "continue", CONTINUE);

  DEFINE_RESERVED(g_next, "next", NEXT);
  DEFINE_RESERVED(g_exit, "exit", EXIT);

  DEFINE_RESERVED(g_delete, "delete", DELETE);

  DEFINE_RESERVED(g_print,   "print",   PRINT);
  DEFINE_RESERVED(g_printf,  "printf",  PRINTF);
  DEFINE_RESERVED(g_getline, "getline", GETLINE);

  DEFINE_RESERVED(g_begin, "BEGIN", BEGIN);
  DEFINE_RESERVED(g_end,   "END",   END);

  // TODO: Use a std::map instead of an array as those have a faster lookup time
  // Then we wont need to loop through them either
  // TODO: Make these be generated automagically
  // TODO: Make this a constexpr vector? those have constexpr initializer_list constructor
  constexpr std::array<TokenTypeWrapper<std::string_view>, 18> g_keywords{
	g_function, g_return,
	g_if, g_else,
	g_do, g_while, g_for, g_in,
	g_break, g_continue,
	g_next, g_exit,
	g_delete,
	g_print, g_printf, g_getline,
	g_begin, g_end
  };
} // namespace keywords

namespace functions {
  // Builtin functions
  // Arithmetic functions:
  DEFINE_RESERVED(g_atan2,    "atan2",    BUILTIN_FUNCTION);
  DEFINE_RESERVED(g_cos,      "cos",      BUILTIN_FUNCTION);
  DEFINE_RESERVED(g_sin,      "sin",      BUILTIN_FUNCTION);
  DEFINE_RESERVED(g_exp,      "exp",      BUILTIN_FUNCTION);
  DEFINE_RESERVED(g_log,      "log",      BUILTIN_FUNCTION);
  DEFINE_RESERVED(g_sqrt,     "sqrt",     BUILTIN_FUNCTION);
  DEFINE_RESERVED(g_int,      "int",      BUILTIN_FUNCTION);
  DEFINE_RESERVED(g_rand,     "rand",     BUILTIN_FUNCTION);
  DEFINE_RESERVED(g_srand,    "srand",    BUILTIN_FUNCTION);

	// String functions:
  DEFINE_RESERVED(g_gsub,     "gsub",     BUILTIN_FUNCTION);
  DEFINE_RESERVED(g_index,    "index",    BUILTIN_FUNCTION);
  DEFINE_RESERVED(g_length,   "length",   BUILTIN_FUNCTION);
  DEFINE_RESERVED(g_match,    "match",    BUILTIN_FUNCTION);
  DEFINE_RESERVED(g_split,    "split",    BUILTIN_FUNCTION);
  DEFINE_RESERVED(g_sprintf,  "sprintf",  BUILTIN_FUNCTION);
  DEFINE_RESERVED(g_sub,      "sub",      BUILTIN_FUNCTION);
  DEFINE_RESERVED(g_substr,   "substr",   BUILTIN_FUNCTION);
  DEFINE_RESERVED(g_tolower,  "tolower",  BUILTIN_FUNCTION);
  DEFINE_RESERVED(g_toupper,  "toupper",  BUILTIN_FUNCTION);

	// IO and general functions:
  DEFINE_RESERVED(g_close,    "close",    BUILTIN_FUNCTION);
  DEFINE_RESERVED(g_system,   "system",   BUILTIN_FUNCTION);

  // TODO: Use a std::map instead of an array as those have a faster lookup time
  // Then we wont need to loop through them either
  // TODO: Make these be generated automagically
  // TODO: Make this a constexpr vector? those have constexpr initializer_list constructor
  constexpr std::array<TokenTypeWrapper<std::string_view>, 21> g_functions{
    g_atan2,
    g_cos,
    g_exp,
    g_log,
    g_sqrt,
    g_int,
    g_rand,
    g_srand,

    g_gsub,
    g_index,
    g_length,
    g_match,
    g_sin,
    g_split,
    g_sprintf,
    g_sub,
    g_substr,
    g_tolower,
    g_toupper,

    g_close,
    g_system
  };
} // namespace functions

// Language reserved symbols
namespace symbols {
  // Braces
  DEFINE_RESERVED(g_paren_open,     '(', PAREN_OPEN);
  DEFINE_RESERVED(g_paren_close,    ')', PAREN_CLOSE);
  DEFINE_RESERVED(g_accolade_open,  '{', ACCOLADE_OPEN);
  DEFINE_RESERVED(g_accolade_close, '}', ACCOLADE_CLOSE);
  DEFINE_RESERVED(g_brace_open,     '[', BRACE_OPEN);
  DEFINE_RESERVED(g_brace_close,    ']', BRACE_CLOSE);

  // Arithmetic operators:
  DEFINE_RESERVED(g_caret,        '^', CARET);
  DEFINE_RESERVED(g_plus,         '+', PLUS);
  DEFINE_RESERVED(g_minus,        '-', MINUS);
  DEFINE_RESERVED(g_asterisk,     '*', ASTERISK);
  DEFINE_RESERVED(g_slash,        '/', SLASH);
  DEFINE_RESERVED(g_percent_sign, '%', PERCENT_SIGN);

  // Assignment variants of Arithmetic operators:
  DEFINE_RESERVED(g_increment, "++", INCREMENT);
  DEFINE_RESERVED(g_decrement, "--", DECREMENT);

  // Assignment:
  // TODO: Rename or structure these better in the future?
  DEFINE_RESERVED(g_power_assignment,    "^=", POWER_ASSIGNMENT);

  DEFINE_RESERVED(g_multiply_assignment, "*=", MULTIPLY_ASSIGNMENT);
  DEFINE_RESERVED(g_divide_assignment,   "/=", DIVIDE_ASSIGNMENT);
  DEFINE_RESERVED(g_modulo_assignment,   "%=", MODULO_ASSIGNMENT);

  DEFINE_RESERVED(g_add_assignment,      "+=", ADD_ASSIGNMENT);
  DEFINE_RESERVED(g_subtract_assignment, "-=", SUBTRACT_ASSIGNMENT);

  DEFINE_RESERVED(g_assignment, '=', ASSIGNMENT);

  // Regex operators:
  DEFINE_RESERVED(g_ere_match,    '~',  ERE_MATCH);
  DEFINE_RESERVED(g_ere_no_match, "!~", ERE_NO_MATCH);

  // Logic operators:
  DEFINE_RESERVED(g_or,  "||", OR);
  DEFINE_RESERVED(g_and, "&&", AND);

  DEFINE_RESERVED(g_not,             '!',   NOT);
  DEFINE_RESERVED(g_less_than,       '<',   LESS_THAN);
  DEFINE_RESERVED(g_less_than_equal, "<=", LESS_THAN_EQUAL);

  DEFINE_RESERVED(g_equal,     "==", EQUAL);
  DEFINE_RESERVED(g_not_equal, "!=", NOT_EQUAL);

  DEFINE_RESERVED(g_greater_than,       '>',   GREATER_THAN);
  DEFINE_RESERVED(g_greater_than_equal, ">=", GREATER_THAN_EQUAL);

  // Control flow symbols:
  DEFINE_RESERVED(g_comma,        ',', COMMA);
  DEFINE_RESERVED(g_dot,          '.', DOT);
  DEFINE_RESERVED(g_question_mark, '?', QUESTION_MARK);
  DEFINE_RESERVED(g_colon,        ':', COLON);
  DEFINE_RESERVED(g_semicolon,    ';', SEMICOLON);

  // Output redirection:
  DEFINE_RESERVED(g_trunc,  '>',  TRUNC);
  DEFINE_RESERVED(g_append, ">>", APPEND);
  DEFINE_RESERVED(g_pipe,   '|',  PIPE);

  // Miscellaneous operators:
  DEFINE_RESERVED(g_dollar_sign,  '$',  DOLLAR_SIGN);
  DEFINE_RESERVED(g_newline,  '\n', NEWLINE);

  // TODO: Make these be generated automagically
  // TODO: Place these  somewhere else they are ugly
  constexpr std::array<TokenTypeWrapper<char>, 26>
  g_single_symbols{
	g_paren_open,
	g_paren_close,
	g_accolade_open,
	g_accolade_close,
	g_brace_open,
	g_brace_close,

	g_assignment,

	g_caret,
	g_plus,
	g_minus,
	g_asterisk,
	g_slash,
	g_percent_sign,

	g_ere_match,

	g_not,
	g_less_than,
	g_greater_than,

	g_comma,
	g_dot,
	g_question_mark,
	g_colon,
	g_semicolon,

	g_trunc,
	g_pipe,

	g_dollar_sign,
	g_newline
  };

  constexpr std::array<TokenTypeWrapper<std::string_view>, 16>
  g_multi_symbols{
	g_increment,
	g_decrement,

	g_power_assignment,

	g_multiply_assignment,
	g_divide_assignment,
	g_modulo_assignment,

	g_add_assignment,
	g_subtract_assignment,

	g_ere_no_match,

	g_or,
	g_and,

	g_less_than_equal,

	g_equal,
	g_not_equal,

	g_greater_than_equal,

	g_append
  };

// Contains symbols that have a special meaning but are not tied to a Token
namespace none {
  // String literal symbols
  DEFINE_RESERVED(g_double_quote, '"', NONE);
  DEFINE_RESERVED(g_backslash, '\\',  NONE);
} // namespace none
} // namespace symbols
} // namespace reserved
// clang-format on

#endif // NEWLANG_TOKEN_RESERVED_RESERVED_HPP
