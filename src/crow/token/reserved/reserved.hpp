#ifndef CROW_CROW_TOKEN_RESERVED_RESERVED_HPP
#define CROW_CROW_TOKEN_RESERVED_RESERVED_HPP

// STL Includes:
#include <map>
#include <type_traits>
#include <utility>

// Library Includes:
#include <boost/assign/list_of.hpp>
#include <boost/bimap.hpp>

// Local Includes:
#include "terminal.hpp"


// Macros:
#define DEFINE_TERMINAL(t_name, t_id, t_token) \
  constexpr Terminal t_name                    \
  {                                            \
    t_id, TokenType::t_token                   \
  }

namespace token::reserved {
// Aliases:
template<typename Key = std::string_view>
using TerminalMap = boost::bimap<Key, TokenType>;

// clang-format off
// Language reserved keywords
namespace keywords {
  // Variables:
  DEFINE_TERMINAL(g_let, "let", LET);
  DEFINE_TERMINAL(g_var, "var", VAR);

  // Package:
  DEFINE_TERMINAL(g_module,  "module", MODULE);
  DEFINE_TERMINAL(g_import,  "import", IMPORT);
  DEFINE_TERMINAL(g_priv,    "priv",   PRIVATE);
  DEFINE_TERMINAL(g_pub,     "pub",    PUBLIC);

  // Typing:
  DEFINE_TERMINAL(g_enum,   "enum",   ENUM);
  DEFINE_TERMINAL(g_struct, "struct", STRUCT);

  // Control statements:
  DEFINE_TERMINAL(g_declare, "declare", DECLARE); // TODO: Consider renaming to just decl.
  DEFINE_TERMINAL(g_macro,   "macro",   MACRO);
  DEFINE_TERMINAL(g_func,    "func",    FUNCTION);
  DEFINE_TERMINAL(g_match,   "match",   MATCH);
  DEFINE_TERMINAL(g_if,      "if",      IF);
  DEFINE_TERMINAL(g_else,    "else",    ELSE);
  DEFINE_TERMINAL(g_elif,    "elif",    ELIF);
  DEFINE_TERMINAL(g_loop,    "loop",    LOOP);

  // Jump:
  DEFINE_TERMINAL(g_break,    "break",    BREAK);
  DEFINE_TERMINAL(g_continue, "continue", CONTINUE);
  DEFINE_TERMINAL(g_defer,    "defer",    DEFER);
  DEFINE_TERMINAL(g_return,   "return",   RETURN);

  // Literals:
  DEFINE_TERMINAL(g_true,  "True",  TRUE);
  DEFINE_TERMINAL(g_false, "False", FALSE);

  // TODO: Convert keywords to boost::bimap.
  // const TerminalMap g_keywords2 = boost::assign::list_of<TerminalMap<std::string_view>::relation>
  // 	(g_let.pair())
  // 	(g_var.pair())
  // 	(g_module.pair()) (g_import.pair()) (g_priv.pair()) (g_pub.pair())
  // 	(g_struct.pair()) (g_interface.pair()) (g_impl.pair())
  //    (g_func.pair())
  // 	(g_match.pair())
  //    (g_if.pair()) (g_else.pair()) (g_elif.pair())
  //    (g_loop.pair())
  //    (g_break.pair()) (g_continue.pair()) (g_defer.pair()) (g_return.pair())
  //    (g_true.pair()) (g_false.pair())
  //    ;

  const std::map g_keywords {
    g_let.pair(), g_var.pair(),
    g_module.pair(), g_import.pair(), g_priv.pair(), g_pub.pair(),
    g_enum.pair(), g_struct.pair(),
    g_declare.pair(), g_macro.pair(),
    g_func.pair(),
    g_match.pair(),
    g_if.pair(), g_else.pair(), g_elif.pair(),
    g_loop.pair(),
    g_break.pair(), g_continue.pair(), g_defer.pair(), g_return.pair(),
    g_true.pair(), g_false.pair()
};

} // namespace keywords

// Language reserved symbols
namespace symbols {
  // Attributes:
  DEFINE_TERMINAL(g_attribute_open,  "[[", ATTRIBUTE_OPEN);
  DEFINE_TERMINAL(g_attribute_close, "]]", ATTRIBUTE_CLOSE);

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
  DEFINE_TERMINAL(g_less_than,       '<',  LESS_THAN);
  DEFINE_TERMINAL(g_less_than_equal, "<=", LESS_THAN_EQUAL);

  DEFINE_TERMINAL(g_equal,     "==", EQUAL);
  DEFINE_TERMINAL(g_not_equal, "!=", NOT_EQUAL);

  DEFINE_TERMINAL(g_greater_than,       '>',  GREATER_THAN);
  DEFINE_TERMINAL(g_greater_than_equal, ">=", GREATER_THAN_EQUAL);

  // Logic:
  DEFINE_TERMINAL(g_not, '!',  NOT);
  DEFINE_TERMINAL(g_or,  "||", OR);
  DEFINE_TERMINAL(g_and, "&&", AND);

  // Miscellaneous:
  DEFINE_TERMINAL(g_arrow,         "->", ARROW);
  DEFINE_TERMINAL(g_dot,           '.',  DOT);
  DEFINE_TERMINAL(g_comma,         ',',  COMMA);
  DEFINE_TERMINAL(g_question_mark, '?',  QUESTION_MARK);
  DEFINE_TERMINAL(g_double_colon,  "::", DOUBLE_COLON);
  DEFINE_TERMINAL(g_colon,         ':',  COLON);
  DEFINE_TERMINAL(g_semicolon,     ';',  SEMICOLON);

  DEFINE_TERMINAL(g_newline,  '\n', NEWLINE);

  const std::map g_single_symbols {
    g_paren_open.pair(),
    g_paren_close.pair(),
    g_accolade_open.pair(),
    g_accolade_close.pair(),
    g_brace_open.pair(),
    g_brace_close.pair(),

    g_assignment.pair(),

    g_less_than.pair(),
    g_greater_than.pair(),

    g_not.pair(),

    g_dot.pair(),
    g_comma.pair(),
    g_question_mark.pair(),
    g_colon.pair(),
    g_semicolon.pair(),

    g_plus.pair(),
    g_minus.pair(),
    g_asterisk.pair(),
    g_slash.pair(),
    g_percent_sign.pair(),

    g_newline.pair()
  };

  const std::map g_multi_symbols{
    g_attribute_open.pair(),
    g_attribute_close.pair(),

    g_increment.pair(),
    g_decrement.pair(),

    g_mul_assign.pair(),
    g_div_assign.pair(),
    g_mod_assign.pair(),

    g_add_assign.pair(),
    g_sub_assign.pair(),

    g_less_than_equal.pair(),

    g_equal.pair(),
    g_not_equal.pair(),

    g_greater_than_equal.pair(),

    g_or.pair(),
    g_and.pair(),

    g_arrow.pair(),
    g_double_colon.pair()
  };

  namespace none {
    constexpr auto g_double_quote{'"'};
    constexpr auto g_backslash{'\\'};

    // These are for dealing with comments:
    constexpr auto g_exclamation_mark{'!'};
    constexpr auto g_slash{'/'};
    constexpr auto g_asterisk{'*'};
    constexpr auto g_newline{'\n'};
  }
} // namespace symbols
} // namespace reserved

// clang-format on

#endif // CROW_CROW_TOKEN_RESERVED_RESERVED_HPP
