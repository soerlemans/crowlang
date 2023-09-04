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
// Miscellaneous:
newline_opt      : // empty
                 | newline_opt NEWLINE
                 ;

terminator       : terminator ';'
                 | terminator NEWLINE
                 | ';'
                 | NEWLINE
                 ;

// Lvalue:
lvalue           : IDENTIFIER
                 | lvalue '[' expr ']'
                 | lvalue '.' newline_opt IDENTIFIER
                 | lvalue ARROW newline_opt IDENTIFIER
                 ;

rvalue           : IDENTIFIER
                 | rvalue '[' expr ']'
				         | rvalue '(' expr_list_opt ')'
                 | rvalue '.' newline_opt IDENTIFIER
                 | rvalue ARROW newline_opt IDENTIFIER
                 ;

function_call    : IDENTIFIER '(' expr_list_opt')'
                 ;

// Literals:
literal          : NUMBER
				         | STRING
				         | TRUE
				         | FALSE
				         ;

grouping         : '(' expr ')'
                 ;

negation         : '!' expr
                 ;

// Prefix:
unary_prefix     : '+' expr
                 | '-' expr
                 ;

// Infix:
arithmetic       : expr '*' newline_opt expr
                 | expr '/' newline_opt expr
                 | expr '%' newline_opt expr
                 | expr '+' newline_opt expr
                 | expr '-' newline_opt expr
                 ;

comparison       : expr LTE newline_opt expr
                 | expr '<' newline_opt expr
                 | expr EQ  newline_opt expr
                 | expr NE  newline_opt expr
                 | expr '>' newline_opt expr
                 | expr GTE newline_opt expr
                 ;

logical          : expr AND newline_opt expr
                 | expr OR  newline_opt expr
                 ;

assignment       : lvalue MUL_ASSIGN newline_opt expr
                 | lvalue DIV_ASSIGN newline_opt expr
                 | lvalue MOD_ASSIGN newline_opt expr
                 | lvalue ADD_ASSIGN newline_opt expr
                 | lvalue SUB_ASSIGN newline_opt expr
                 | lvalue '=' newline_opt expr
                 ;

// Expressions:
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

expr_opt         : // empty
				         | expr
                 ;

decl_expr        : Let IDENTIFIER
                 | Let IDENTIFIER '=' newline_opt expr
                 | Let IDENTIFIER ':' IDENTIFIER '=' newline_opt expr
                 ;

eval_expr        : decl_expr ';' expr
                 | expr
                 | expr ';' expr
                 ;

expr_statement   : assignment terminator
				         | 
                 ;

// Expression lists:
multiple_expr_list : expr ',' newline_opt expr
                 | multiple_expr_list ',' newline_opt expr
                 ;

expr_list        : expr
                 | multiple_expr_list
                 ;

expr_list_opt    : // empty
                 | expr_list
                 ;

// Jump statement:
jump_statement   : Continue terminator
                 | Break terminator
				         | Defer expr_statement
				         | Defer body
                 | Return expr_opt terminator
                 ;

// Loop statement:
loop_statement   : Loop body
				         | Loop eval_expr body
				         | Loop eval_expr ';' expr body
                 ;

// Match statement:
match_case      :
                ;

match_case_list  : match_case
                 | match_case_list match_case
                 ;

match_body       : newline_opt '{' match_case_list '}'
                 ;

match_statement  : Match match_body
                 | Match eval_expr match_body
                 ;

// Branch statements:
if_statement     : If eval_expr body
				         | If eval_expr body Else body
				         | If eval_expr body elif_statement
                 ;

elif_statement   : ElIf eval_expr body
				         | ElIf eval_expr body Else body
				         | ElIf eval_expr body elif_statement
                 ;

// Statements:
statement        : decl_expr terminator
				         | expr_statement
				         | if_statement
				         | match_statement
				         | loop_statement
				         | jump_statement
				         | body
                 ;

statement_list   : statement newline_opt
                 | statement_list statement newline_opt
                 ;

// Body:
body             : newline_opt '{' newline_opt '}'
                 | newline_opt '{' newline_opt statement_list newline_opt '}'
                 ;

// Attributes:
attribute        : Private
				         | Public
                 ;

// Function:
param_list       : IDENTIFIER ':' IDENTIFIER
                 | param_list ',' IDENTIFIER ':' IDENTIFIER
                 ;

param_list_opt   : // empty
                 | param_list
                 ;

return_type_opt  : // empty
                 | newline_opt ARROW IDENTIFIER
                 ;

lambda           : Fn '(' param_list_opt ')' return_type_opt body
                 | Fn return_type_opt body
                 ;

function         : Fn IDENTIFIER '(' param_list_opt ')' return_type_opt body
                 | Fn IDENTIFIER return_type_opt body
				         ;

// Import:
import_expr      : STRING newline_opt
                 | IDENTIFIER '=' STRING newline_opt
                 ;

import_list      : import_expr
                 | import_list import_expr
                 ;

import           : Import STRING
                 | Import '(' newline_opt import_list ')'
                 ;

// Packaging:
package          : Package IDENTIFIER
                 ;

// Items:
item             : package
				         | import
				         | decl_expr
                 | function
                 ;

item_list        : // empty
                 | newline_opt item
                 | item_list newline_opt item
                 ;

program          : item_list
                 | item_list item
                 ;

%%
