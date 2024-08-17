Crowlang
========
![Logo](assets/crowlang_banner.png)

This project is me experimenting with creating my own programming language.
For this project I am using C++23.

Crow's syntax is inspired by Swift and Rust.
Semicolons are completely optional in Crow.

## Dependencies
In order to compile the project you will need to following dependencies:

- C++ compiler with support for C++23
- [Invoke](https://www.pyinvoke.org/) (Used to invoke CMake and scripts)
- [Cmake](https://cmake.org/)  (Main buildsysstem)
- [CLI11](https://github.com/CLIUtils/CLI11) (CLI option parsing library)
- [rang](https://github.com/agauniyal/rang/tree/master) (cross platform terminal coloring library)
- [tabulate](https://github.com/p-ranav/tabulate) (Text table library)
- [Boost](https://www.boost.org/) (Utility libraries for C++)
- [LLVM](https://llvm.org) (LLVM is used for code generation and optimization)
- [libclang](https://clang.llvm.org/doxygen/group__CINDEX.html) (libclang for compiling C++ sources (part of the LLVM project.))
- [cereal](https://uscilab.github.io/cereal/) (Serialization library used for the AST)
- [libassert](https://github.com/jeremy-rifkin/libassert) (Modern assertion library for compile and runtime assertion checking)

### Buildsystem
In order to compile the project you will need `invoke`, `clang` and `cmake`.
You can install most of the dependencies with the following aptitude command:

```shell
apt install -y pipx clang cmake extra-cmake-modules
```

In order to make use of invoke you should install it through `pipx`:

```shell
pipx install invoke
```

### Dynamic libraries
Rang and tabulate are downloaded using CMake and statically linked.
CLI11, Boost, LLVM and libclang are dynamically linked (CMake searches for it on your system).
You can install the dependencies with the following aptitude command:

```shell
apt install -y libcurl4 libcli11-dev llvm-17-dev libclang-17-dev liblld-17-dev libboost-all-dev libzstd-dev
```

## Project documentation

 - `cmake/` Cmake sources that are needed to build the project.
 - `src/` Sources of the Crow project.
 - `tests/` Unit tests of the Crow project.
 - `samples/` Crow sources that can be compiled to demonstrate the functionalities of Crow.
 - `tools/` Collection of tools and scripts, that aid development.
