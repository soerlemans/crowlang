#ifndef CROW_TOKEN_RESERVED_RESERVED_HPP
#define CROW_TOKEN_RESERVED_RESERVED_HPP

// STL Includes:
#include <array>
#include <type_traits>
#include <utility>

// Local Includes:
#include "terminal.hpp"


namespace token::reserved {
// Macros:
#define DEFINE_TERMINAL(t_name, t_id, t_token) \
  constexpr Terminal t_name                    \
  {                                            \
    t_id, TokenType::t_token                   \
  }

// clang-format off
// Language reserved keywords
namespace keywords {
	// Variables:
  DEFINE_TERMINAL(g_let,   "let",   LET);
  DEFINE_TERMINAL(g_const, "const", CONST);

  // Package:
  DEFINE_TERMINAL(g_package, "pkg",    PACKAGE);
  DEFINE_TERMINAL(g_import,  "import", IMPORT);
  DEFINE_TERMINAL(g_priv,    "priv",   PRIVATE);
  DEFINE_TERMINAL(g_pub,     "pub",    PUBLIC);

  // Object oriented:
  DEFINE_TERMINAL(g_struct,    "struct",    STRUCT);
  DEFINE_TERMINAL(g_interface, "interface", INTERFACE);

  // Control statements:
  DEFINE_TERMINAL(g_fn,    "fn",    FUNCTION);
  DEFINE_TERMINAL(g_match, "match", MATCH);
  DEFINE_TERMINAL(g_if,    "if",    IF);
  DEFINE_TERMINAL(g_else,  "else",  ELSE);
  DEFINE_TERMINAL(g_loop,  "loop",  LOOP);

  // Jump:
  DEFINE_TERMINAL(g_break,    "break",    BREAK);
  DEFINE_TERMINAL(g_continue, "continue", CONTINUE);
  DEFINE_TERMINAL(g_defer,    "defer",    DEFER);
  DEFINE_TERMINAL(g_return,   "return",   RETURN);

  // TODO: Use a std::map instead of an array as those have a faster lookup time
  // Then we wont need to loop through them either
  constexpr std::array g_keywords{
		g_let, g_const,
		g_package, g_import, g_priv, g_pub,
		g_struct, g_interface,
	  g_fn,
		g_match,
	  g_if, g_else,
	  g_loop,
	  g_break, g_continue, g_defer, g_return
  };
} // namespace keywords

// Language reserved symbols
namespace symbols {
  // Braces
  DEFINE_TERMINAL(g_paren_open,     '(', PAREN_OPEN);
  DEFINE_TERMINAL(g_paren_close,    ')', PAREN_CLOSE);
  DEFINE_TERMINAL(g_accolade_open,  '{', ACCOLADE_OPEN);
  DEFINE_TERMINAL(g_accolade_close, '}', ACCOLADE_CLOSE);
  DEFINE_TERMINAL(g_brace_open,     '[', BRACE_OPEN);
  DEFINE_TERMINAL(g_brace_close,    ']', BRACE_CLOSE);

  // Assignment variants of Arithmetic operators:
  DEFINE_TERMINAL(g_plus,         '+', PLUS);
  DEFINE_TERMINAL(g_minus,        '-', MINUS);
  DEFINE_TERMINAL(g_asterisk,     '*', ASTERISK);
  DEFINE_TERMINAL(g_slash,        '/', SLASH);
  DEFINE_TERMINAL(g_percent_sign, '%', PERCENT_SIGN);

  DEFINE_TERMINAL(g_increment, "++", INCREMENT);
  DEFINE_TERMINAL(g_decrement, "--", DECREMENT);

  // Assignment:
  DEFINE_TERMINAL(g_mul_assign, "*=", MUL_ASSIGN);
  DEFINE_TERMINAL(g_div_assign, "/=", DIV_ASSIGN);
  DEFINE_TERMINAL(g_mod_assign, "%=", MOD_ASSIGN);

  DEFINE_TERMINAL(g_add_assign, "+=", ADD_ASSIGN);
  DEFINE_TERMINAL(g_sub_assign, "-=", SUB_ASSIGN);

  DEFINE_TERMINAL(g_assignment, '=',  ASSIGNMENT);

	// Comparisons:
  DEFINE_TERMINAL(g_less_than,       '<',   LESS_THAN);
  DEFINE_TERMINAL(g_less_than_equal, "<=", LESS_THAN_EQUAL);

  DEFINE_TERMINAL(g_equal,     "==", EQUAL);
  DEFINE_TERMINAL(g_not_equal, "!=", NOT_EQUAL);

  DEFINE_TERMINAL(g_greater_than,       '>',   GREATER_THAN);
  DEFINE_TERMINAL(g_greater_than_equal, ">=", GREATER_THAN_EQUAL);

  // Logic:
  DEFINE_TERMINAL(g_true, "true",  TRUE);
  DEFINE_TERMINAL(g_false, "false",  FALSE);

  DEFINE_TERMINAL(g_not, '!',  NOT);
  DEFINE_TERMINAL(g_or,  "||", OR);
  DEFINE_TERMINAL(g_and, "&&", AND);

  // Miscellaneous:
  DEFINE_TERMINAL(g_arrow,         "->", ARROW);
  DEFINE_TERMINAL(g_dot,           '.',  DOT);
  DEFINE_TERMINAL(g_comma,         ',',  COMMA);
  DEFINE_TERMINAL(g_question_mark, '?',  QUESTION_MARK);
  DEFINE_TERMINAL(g_colon,         ':',  COLON);
  DEFINE_TERMINAL(g_semicolon,     ';',  SEMICOLON);

  DEFINE_TERMINAL(g_newline,  '\n', NEWLINE);

  constexpr std::array g_single_symbols{
	  g_paren_open,
	  g_paren_close,
	  g_accolade_open,
	  g_accolade_close,
	  g_brace_open,
	  g_brace_close,

	  g_assignment,

	  g_less_than,
	  g_greater_than,

	  g_not,

	  g_dot,
	  g_comma,
	  g_question_mark,
	  g_colon,
	  g_semicolon,

	  g_plus,
	  g_minus,
	  g_asterisk,
	  g_slash,
	  g_percent_sign,

		g_newline
  };

  constexpr std::array g_multi_symbols{
	  g_increment,
	  g_decrement,

	  g_mul_assign,
	  g_div_assign,
	  g_mod_assign,

	  g_add_assign,
	  g_sub_assign,

	  g_less_than_equal,

	  g_equal,
	  g_not_equal,

	  g_greater_than_equal,

	  g_true,
	  g_false,

	  g_or,
	  g_and,

		g_arrow
	};

	namespace none {
		constexpr char g_double_quote{'"'};
		constexpr char g_backslash{'\\'};
	}
} // namespace symbols
} // namespace reserved
// clang-format on

#endif // CROW_TOKEN_RESERVED_RESERVED_HPP
