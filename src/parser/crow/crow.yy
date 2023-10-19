// Values
%token IDENTIFIER NUMBER STRING

// Variables:
%token Let Const

// Package:
%token Module Import Private Public

// Typing:
%token Enum Struct Interface Impl

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
                 | lvalue newline_opt '.' IDENTIFIER
                 | lvalue newline_opt ARROW IDENTIFIER
                 ;

chain_expr       : IDENTIFIER
                 | chain_expr '[' expr ']'
				         | chain_expr '(' expr_list_opt ')'
                 | chain_expr newline_opt '.' IDENTIFIER
                 | chain_expr newline_opt ARROW IDENTIFIER
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

precrement       : INCREMENT lvalue
				         | DECREMENT lvalue
                 ;

postcrement      : lvalue INCREMENT
				         | lvalue DECREMENT
                 ;

// Infix:
arithmetic       : expr newline_opt '*' expr
                 | expr newline_opt '/' expr
                 | expr newline_opt '%' expr
                 | expr newline_opt '+' expr
                 | expr newline_opt '-' expr
                 ;

comparison       : expr newline_opt LTE expr
                 | expr newline_opt '<' expr
                 | expr newline_opt EQ  expr
                 | expr newline_opt NE  expr
                 | expr newline_opt '>' expr
                 | expr newline_opt GTE expr
                 ;

logical          : expr newline_opt AND expr
                 | expr newline_opt OR  expr
                 ;

// Expressions:
expr             : lvalue
				         | literal
                 | grouping
                 | unary_prefix
                 | negation
                 | precrement
                 | postcrement
				         | function_call
                 | arithmetic
                 | comparison
                 | logical
                 ;

expr_opt         : // empty
				         | expr
                 ;

// TODO: Refactor Const and Let to be more elegant
const_expr       : Const IDENTIFIER '=' newline_opt expr
                 | Const IDENTIFIER ':' IDENTIFIER '=' newline_opt expr
                 ;

let_expr         : Let IDENTIFIER ':' IDENTIFIER
                 | Let IDENTIFIER '=' newline_opt expr
                 | Let IDENTIFIER ':' IDENTIFIER '=' newline_opt expr
                 ;

decl_expr        : const_expr
                 | let_expr
                 ;

eval_expr        : decl_expr ';' expr
                 | expr
                 | expr ';' expr
                 ;

expr_statement   : expr terminator
                 ;

// Result statement:
assignment       : lvalue MUL_ASSIGN newline_opt expr
                 | lvalue DIV_ASSIGN newline_opt expr
                 | lvalue MOD_ASSIGN newline_opt expr
                 | lvalue ADD_ASSIGN newline_opt expr
                 | lvalue SUB_ASSIGN newline_opt expr
                 | lvalue '=' newline_opt expr
                 ;

result_statement : decl_expr terminator
				         | assignment terminator
				         | function_call terminator
				         | precrement terminator
				         | postcrement terminator
				         /* | ';' */
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
statement        : result_statement
				         | if_statement
				         | match_statement
				         | loop_statement
				         | keyword_statement
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

// Typing:
// TODO:
/* alias_def        : Use? */

// Enum:
enum_def         : Enum IDENTIFIER newline_opt
                     '{' newline_opt '}'
                 ;
// Interface:
method_decl      : Fn IDENTIFIER '(' param_list_opt ')' return_type terminator
                 ;


method_decl_list : // empty
				         | method_decl
				         | fn_decl_list method_decl
                 ;

interface_def    : Interface IDENTIFIER newline_opt
                     '{' newline_opt method_decl_list '}'
                 ;

// Struct:
member_decl      : IDENTIFIER ':' IDENTIFIER terminator
                 ;

member_decl_list : // empty
                 | member_decl
				         | member_decl_list member_decl
                 ;

struct_def       : Struct IDENTIFIER newline_opt
                     '{'  newline_opt member_decl_list '}'
                 ;

type_def         : enum_def
				         | interface_def
				         | struct_def
                 ;

// Implementation:
def_list         : newline_opt function
                 | impl_list newline_opt function
                 ;

def_block        : Def IDENTIFIER newline_opt
                   '{' impl_list '}'
                 | Def IDENTIFIER newline_opt
                   '{' impl_list '}'
                 ;

// Function:
// TODO: Think about having in, out and inout specifiers like ADA?
param_list       : IDENTIFIER ':' IDENTIFIER
                 | param_list ',' IDENTIFIER ':' IDENTIFIER
                 ;

param_list_opt   : // empty
                 | param_list
                 ;

return_type      : newline_opt ARROW IDENTIFIER
                 ;

return_type_opt  : // empty
                 | return_type
                 ;

lambda           : Fn '(' param_list_opt ')' return_type_opt body
                 | Fn return_type_opt body
                 ;

function         : Fn IDENTIFIER '(' param_list_opt ')' return_type_opt body
                 | Fn IDENTIFIER return_type_opt body
				         ;

function_call    : chain_expr '(' expr_list_opt')'
                 ;

// Import:
import_expr      : STRING
                 | IDENTIFIER '=' STRING
                 ;

import_list      : import_expr newline_opt
                 | import_list terminator import_expr newline_opt
                 ;

import           : Import STRING
                 | Import '(' newline_opt import_list ')'
                 ;

// Packaging:
module           : Module IDENTIFIER
                 ;

// Items:
item             : module
				         | import
				         | type_def
				         | decl_expr
                 | function
                 | impl_block
                 ;

item_list        : // empty
                 | newline_opt item
                 | item_list newline_opt item
                 ;

program          : item_list
                 | item_list item
                 ;

%%
