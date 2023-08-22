/* Values */
%token IDENTIFIER NUMBER STRING

/* Variables */
%token Let Const

/* Package */
%token Package Import Private Public

/* Typing */
%token Struct Interface

/* Control Statements*/
%token Fn Switch Case If Else Loop

/* Control Flow */
%token Break Continue Defer Return

/* Arithmetic */
%token '+' '-' '*' '/' '%'
%token INCREMENT DECREMENT

/* Assignment */
%token MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN SUB_ASSIGN
%token '='

/* Logical */
%token TRUE FALSE

%token '!'
%token OR AND

/* Comparison */
%token LTE EL EQ NE GE GTE

/* Miscellaneous */
%token ARROW '.' ',' '?' ':' ';'
%token NEWLINE

%start program
%%

program          : item_list
                 | item_list item
                 ;

item_list        : /* empty */
                 | item_list item terminator
                 ;

item             : Package IDENTIFIER
				         | import
                 | function
                 ;

import           : Import STRING
                 ;

attribute        :
                 ;

// Function:
function         : Fn IDENTIFIER '(' param_list ')' body
                 | Fn IDENTIFIER body
				         ;

lambda           : Fn '(' param_list ')' body
                 | Fn body
                 ;

param_list_opt   : /* empty */
                 | param_list
                 ;

param_list       : IDENTIFIER
                 | param_list ',' IDENTIFIER
                 ;

// Body:
body             : newline_opt '{' newline_opt                  '}'
                 | newline_opt '{' newline_opt statement_list   '}'
                 ;

// Statements:
statement_list   : statement
                 | statement_list statement
                 ;

statement        : body
				         | expr_statement
				         | if_statement
				         | switch_statement
				         | loop_statement
				         | jump_statement
                 ;

// If statement:
if_statement     : If expr body
				         | If expr body Else body

// Switch statement:
switch_statement : Switch switch_body
                 ;

switch_body      : newline_opt '{' switch_case_list '}'
                 ;

switch_case_list : switch_case
                 | switch_case_list switch_case
                 ;

switch_case      : Case body
                 ;

// Loop statement:
loop_statement   : Loop expr body
				         | Loop decl_expr ';' expr_statement expr body
                 ;

// Jump statement:
jump_statement   : Continue
                 | Break
				         | Defer body
                 | Return
                 | Return expr
                 ;

// Expressions:
expr_statement   : expr terminator ;

expr             : ;

decl_expr        : Let IDENTIFIER
                 | decl_expr '=' expr
                 ;

unary_expr       : '+' expr
				         | '-' expr

// Literals:
bool_lit         : TRUE
				         | FALSE
                 ;

// Miscellaneous:
terminator       : terminator NEWLINE
                 | ';'
                 | NEWLINE
                 ;

newline_opt      : /* empty */
                 | newline_opt NEWLINE
                 ;

%%
