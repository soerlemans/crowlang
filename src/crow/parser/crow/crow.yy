// Values
%token IDENTIFIER NUMBER STRING

// Variables:
%token Let Var

// Package:
%token Module Import Private Public

// Meta:
%token Declare
%token ATTRIBUTE_OPEN ATTRIBUTE_CLOSE

// Typing:
%token Enum Struct Self Proto

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
                 ;

// Lvalue Infix:
lvalue_expr      : lvalue
                 | lvalue lvalue_chain_expr
                 ;

// Chain:
// Note lets not allow ending in () for lvalue chain expressions.
lvalue_chain_expr : '.' newline_opt lvalue
                  | '[' expr ']' newline_opt
                  | '(' expr_list_opt ')' newline_opt
                  ;

// | '.' '(' expr_list_opt ')'
chain_expr       : lvalue_chain_expr
                 | '.' newline_opt function_call
                 ;

lvalue_chain_expr_list : lvalue_chain_expr
                       | lvalue_chain_expr_list lvalue_chain_expr
                       ;

chain_expr_list  : chain_expr
                 | chain_expr_list chain_expr
                 ;

lvalue_chain_expr_list_opt : // empty
                           | lvalue_chain_expr_list
                           ;

chain_expr_list_opt : // empty
                    | chain_expr_list
                    ;

// Literals:
literal          : NUMBER
                 | STRING
                 | TRUE
                 | FALSE
                 ;

literal_list     : literal
                 | literal_list ',' newline_opt literal
                 ;

expr_list_opt    : // empty
                 | expr_list
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

// FIXME: Following expressions cause side effects thus should be valid as a loose expression.
// function_call should be valid in an expression but should not be a free_expr.

// function_call

// FIXME: We should handle postcrement like Go where it is a statement not an expression.

expr             : lvalue
		             | literal
                 | grouping
                 | unary_prefix
                 | negation
		             | function_call
                 | arithmetic
                 | comparison
                 | logical
                 ;

expr_opt         : // empty
				         | expr
                 ;

// TODO: Refactor Var and Let to be more elegant.
// TODO: Add block definitions like in Golang (using parenthesis).
let_expr         : Let IDENTIFIER ':' type_specifier
                 | Let IDENTIFIER '=' newline_opt expr
                 | Let IDENTIFIER ':' type_specifier '=' newline_opt expr
                 ;

var_expr         : Var IDENTIFIER ':' type_specifier
                 | Var IDENTIFIER '=' newline_opt expr
                 | Var IDENTIFIER ':' type_specifier '=' newline_opt expr
                 ;

binding_expr     : var_expr
                 | let_expr
                 ;

eval_expr        : binding_expr ';' expr
                 | expr
                 ;

expr_statement   : expr terminator
                 ;

// Result statement:
assignment       : lvalue_expr MUL_ASSIGN newline_opt expr
                 | lvalue_expr DIV_ASSIGN newline_opt expr
                 | lvalue_expr MOD_ASSIGN newline_opt expr
                 | lvalue_expr ADD_ASSIGN newline_opt expr
                 | lvalue_expr SUB_ASSIGN newline_opt expr
                 | lvalue_expr '=' newline_opt expr
		             | lvalue_expr INCREMENT
		             | lvalue_expr DECREMENT
                 ;

result_statement : binding_expr terminator
                 | assignment terminator
                 | function_call terminator
                 ;

// Expression lists:
expr_list        : expr
                 | expr_list ',' newline_opt expr
                 ;


expr_list_opt    : // empty
                 | expr_list
                 ;

// Jump statement:
// Continue and Break are only allowed to be used in loops.
jump_statement   : Continue terminator
                 | Break terminator
                 | Defer expr_statement
                 | Defer body
                 | Return expr_opt terminator
                 ;

// Loop statement:
// FIXME: Expr and assignment both accept lvalue's.
// So we cannot distinguish using the top-down parser.
// We need to figure out a workaround or leave as is.
loop_statement   : Loop body
                 | Loop eval_expr body
                 | Loop eval_expr ';' assignment body
                 ;

// Match statement:
match_case      : '.'
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

// Typing:
// TODO: Deal with more complex type specifications/expressions.
// Just looking at an identifier is not enough anymore (or it wont be).
type_expr        :
                 ;

// TODO: Figure out how to name aliases?
/* alias_def     : Alias? */
type_specifier   : IDENTIFIER
                 | * type_specifier
                 | & type_specifier
								 ;

// Enum:
enum_def         : Enum IDENTIFIER newline_opt
                     '{' newline_opt '}'
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
				         | struct_def
                 ;

// Function:
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

// lambda           : Func '(' param_list_opt ')' return_type_opt body
//                  | Func return_type_opt body
//                  ;

// We detect methods by the receiver which will give them access to the self keyword.
function         : Func IDENTIFIER '(' param_list_opt ')' return_type_opt body
                 | Func '(' IDENTIFIER ')' IDENTIFIER '(' param_list_opt ')' return_type_opt body
				         ;

function_call    : IDENTIFIER '(' expr_list_opt')'
                 ;

// Meta:
attribute_item   : attribute
                 | declare
                 | binding_expr
                 | function
                 ;

attribute_item_list : attribute_item newline_opt
                    | attribute_item_list newline_opt attribute_item
                    ;

attribute_body   : attribute_item
                 | '{' newline_opt attribute_item_list'}'
								 ;

attribute        : ATTRIBUTE_OPEN identifier ATTRIBUTE_CLOSE newline_opt attribute_body
		             | ATTRIBUTE_OPEN identifier '(' literal_list ')' ATTRIBUTE_CLOSE newline_opt attribute_body
                 ;


declare          : Declare Let IDENTIFIER : IDENTIFIER newline_opt
                 | Declare Var IDENTIFIER : IDENTIFIER newline_opt
                 | Declare Func IDENTIFIER '(' param_list_opt ')' return_type_opt newline_opt
                 | Declare Struct IDENTIFIER newline_opt
								 | /* TODO: Add method declarations. */
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

// Package:
module_decl      : Module IDENTIFIER
                 ;

// TODO: Figure out, we want inline modules and namespaces.
// inline_module_decl : Module IDENTIFIER '{' item_list '}
//                    ;

// Items:
item             : module_decl
				         | import
								 | declare
								 | attribute
				         | type_def
				         | binding_expr
                 | function
                 | impl_block
                 ;

item_list        : module_decl
                 | newline_opt item
                 | item_list newline_opt item
                 ;

program          : item_list
                 | item_list item
                 ;

%%
