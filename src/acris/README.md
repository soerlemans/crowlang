README
======
Here is some project documentation about each directory.
These are in order of when they are used:

 1. `container/`: Container classes used in the compiler.
 2. `diagnostics/`: Contains user caused errors thrown in the compiler.
 3. `debug/`: Debug utilities for debugging the application.
 4. `settings/`: Contains utilities for the compiler settings.
 5. `state/`: Keeps track of the state of compilation of a translation unit or compilation unit.

 Compiler phases:
 1. `token/`: Specifies the tokens
 2. `lexer/`: Contains lexer of the compiler.
 3. `parser/`: Contains parser of the compiler.
 4. `ast/`: Contains the abstract syntax tree of the compiler, represented using a class hierarchy.
 5. `semantic/`: Contains utilities for verifying the semantic validity of the AST.
 6. `codegen/`: Contains the code generation utilities of the compiler.
