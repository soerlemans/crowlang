// Values
%token IDENTIFIER NUMBER STRING

// Variables:
%token Let Const

// Package:
%token Package Import Private Public

// Typing:
%token Struct Interface

// Control Statements:
%token Fn Match Case If Else ElIf Loop

// Control Flow:
%token Break Continue Defer Return

// Arithmetic:
%token '+' '-' '*' '/' '%'
%token INCREMENT DECREMENT

// Assignment:
%token MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN SUB_ASSIGN
%token '='

// Logical:
%token TRUE FALSE

%token '!'
%token OR AND

// Comparison:
%token LTE EL EQ NE GE GTE

// Miscellaneous:
%token ARROW '.' ',' '?' ':' ';'
%token NEWLINE

%start program
%%

program          : item_list
                 | item_list item
                 ;

item_list        : // empty
                 | newline_opt item
                 | item_list newlinte_opt item
                 ;

item             : package
				         | import
                 | function
                 ;

// Packaging:
package          : Package IDENTIFIER
                 ;

import           : Import STRING
                 | Import '(' newline_opt import_list ')'
                 ;

import_list      : import_expr
                 | import_list import_expr
                 ;

import_expr      : STRING newline_opt
                 | IDENTIFIER '=' STRING newline_opt
                 ;

attribute        : Private
				         | Public
                 ;

// Function:
function         : Fn IDENTIFIER '(' param_list ')' body
                 | Fn IDENTIFIER body
				         ;

return_type_opt  : // empty
                 | newline_opt ARROW IDENTIFIER
                 ;

lambda           : Fn '(' param_list ')' body
                 | Fn body
                 ;

param_list_opt   : // empty
                 | param_list
                 ;

param_list       : IDENTIFIER
                 | param_list ',' IDENTIFIER
                 ;

// Body:
body             : newline_opt '{' newline_opt '}'
                 | newline_opt '{' newline_opt statement_list newline_opt '}'
                 ;

// Statements:
statement_list   : statement newline_opt
                 | statement_list statement newline_opt
                 ;

statement        : decl_expr terminator
				         | expr_statement
				         | if_statement
				         | match_statement
				         | loop_statement
				         | jump_statement
				         | body
                 ;

// If statement:
if_statement     : If eval_expr body
				         | If eval_expr body Else body
				         | If eval_expr body elif_statement
                 ;

elif_statement   : ElIf eval_expr body
				         | ElIf eval_expr body Else body
				         | ElIf eval_expr body elif_statement
                 ;

// Match statement:
match_statement  : Match match_body
                 | Match eval_expr match_body
                 ;

match_body      : newline_opt '{' match_case_list '}'
                 ;

match_case_list : match_case
                 | match_case_list match_case
                 ;

match_case      :
                ;

// Loop statement:
loop_statement   : Loop body
				         | Loop eval_expr body
				         | Loop eval_expr ';' expr body
                 ;

// Jump statement:
jump_statement   : Continue terminator
                 | Break terminator
				         | Defer expr_statement
				         | Defer body
                 | Return expr_opt terminator
                 ;

// Expressions:
expr_statement   : expr terminator
                 ;

expr_list_opt    : // empty
                 | expr_list
                 ;

expr_list        : expr
                 | multiple_expr_list
                 ;

multiple_expr_list : expr ',' newline_opt expr
                 | multiple_expr_list ',' newline_opt expr
                 ;

expr_opt         : // empty
				         | expr
                 ;

expr             : unary_prefix
                 | grouping
                 | negation
                 | arithmetic
                 | comparison
                 | logical
				         | literal
                 | lvalue
                 | INCREMENT lvalue
                 | DECREMENT lvalue
                 | assignment
                 | IDENTIFIER '(' expr_list_opt ')'
                 ;

unary_prefix     : '+' expr
                 | '-' expr
                 ;

grouping         : '(' expr ')'
                 ;

negation         : '!' expr
                 ;

arithmetic       : expr '*' expr
                 | expr '/' expr
                 | expr '%' expr
                 | expr '+' expr
                 | expr '-' expr
                 ;

comparison       : expr LTE expr
                 | expr '<' expr
                 | expr EQ  expr
                 | expr NE  expr
                 | expr '>' expr
                 | expr GTE expr
                 ;

logical          : expr AND expr
                 | expr OR  expr
                 ;

assignment       : lvalue MUL_ASSIGN expr
                 | lvalue DIV_ASSIGN expr
                 | lvalue MOD_ASSIGN expr
                 | lvalue ADD_ASSIGN expr
                 | lvalue SUB_ASSIGN expr
                 | lvalue '=' expr
                 ;

eval_expr        : decl_expr ';' expr
                 | expr
                 | expr ';' expr
                 ;

decl_expr        : Let IDENTIFIER
                 | Let IDENTIFIER '=' expr
                 | Let IDENTIFIER ':' IDENTIFIER '=' expr
                 ;

// Literals:
literal          : NUMBER
				         | STRING
				         | bool_lit
				         ;

bool_lit         : TRUE
				         | FALSE
                 ;

// Lvalue:
lvalue           : IDENTIFIER
                 | IDENTIFIER '[' expr ']'
                 ;

// Miscellaneous:
terminator       : terminator ';'
                 | terminator NEWLINE
                 | ';'
                 | NEWLINE
                 ;

newline_opt      : // empty
                 | newline_opt NEWLINE
                 ;

%%
