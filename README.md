Crow
====
This project is my experimentation with creating my own programming language.
For this project I am using C++23.

Crow's syntax is inspired by Swift and Rust.
Semicolons are completely optional in Crow.

## Dependencies
I aim to keep dependencies to a minimum but the following is required:

- C++ compiler with support for C++23
- Make (Used to invoke CMake and scripts)
- Cmake  (Main buildsysstem)
- [CLI11](https://github.com/CLIUtils/CLI11) (CLI option parsing library)
- [rang](https://github.com/agauniyal/rang/tree/master) (cross platform terminal coloring library)
- [tabulate](https://github.com/p-ranav/tabulate) (Text table library)
- [LLVM](https://llvm.org) (LLVM codegen library)

Rang and tabulate are downloaded using CMake and statically linked but CLI11 and LLVM are dynamically linked (CMake searches for it on your system).
You can install the dependencies with the following aptitude command:

```shell
apt install -y libcli11-dev llvm-14-dev
```

## Progress
Crow is currently in active development and is currently not even at version 0.1.0.
This section will promptly describe Crow's roadmap:


## Version 0.1.0
To reach this version the following must be implemented:

- [x] Grammar
  - [x] Statements
    - [x] Let
    - [x] Assignment
    - [x] Control statements (if, loop, else, elif)
    - [x] Expressions (arithmetic, comparison, logical, postcrement)
  - [x] Modules & Imports
  - [x] Functions
  - [x] Interfaces
  - [] Structs
  - [] Implementation

## Version 0.2.0
To reach this version the following must be implemented:

- [x] Lexer
  - [x] Identifiers
  - [x] Keywords
  - [x] Literals
  - [x] Symbols
    - [x] Single symbols
    - [x] Multi symbols

## Version 0.3.0
To reach this version the following must be implemented:

- [x] Parser
  - [x] Statements
    - [x] Let
    - [x] Assignment
    - [x] Control statements (if, loop, else, elif)
    - [x] Expressions (arithmetic, comparison, logical, postcrement)
	  - [x] Operator precedence
  - [x] Modules & Imports
  - [x] Functions
  - [x] Interfaces
  - [x] Modules
  - [x] Imports
  - [x] Functions
  - [x] Interfaces
  - [] Structs
  - [] Implementation

## Version 0.4.0
To reach this version the following must be implemented:

- [] Code generation
  - [] LLVM
  - [] Tree walk interpreter

## Version 0.5.0
To reach this version the following must be implemented:

 - [] Benchmarking
   - [] Callgrind
 - [] Peephole optimization

### Version 1.0.0
To reach this version the following must be implemented:

- [] Builtin functions/Standard library
