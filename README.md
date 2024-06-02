Crow
====
This project is me experimentation with creating my own programming language.
For this project I am using C++23.

Crow's syntax is inspired by Swift and Rust.
Semicolons are completely optional in Crow.

## Dependencies
In order to compile the project you will need to following dependencies:

- C++ compiler with support for C++23
- Make (Used to invoke CMake and scripts)
- [Cmake](https://cmake.org/)  (Main buildsysstem)
- [CLI11](https://github.com/CLIUtils/CLI11) (CLI option parsing library)
- [rang](https://github.com/agauniyal/rang/tree/master) (cross platform terminal coloring library)
- [tabulate](https://github.com/p-ranav/tabulate) (Text table library)
- [Boost]() (Utility libraries for C++)
- [LLVM](https://llvm.org) (LLVM for code generation and optimization)
- [libclang](https://clang.llvm.org/doxygen/group__CINDEX.html) (libclang for compiling C++ sources (part of the LLVM project.))

### Buildsystem
In order to compile the project you will need clang, invoke and cmake.
You can install the dependencies with the following aptitude command:

```shell
apt install -y build-essential clang cmake extra-cmake-modules
```

### Dynamic libraries
Rang and tabulate are downloaded using CMake and statically linked.
CLI11, Boost, LLVM and libclang are dynamically linked (CMake searches for it on your system).
You can install the dependencies with the following aptitude command:

```shell
apt install -y libcli11-dev libcurl4 libboost-all-dev libzstd-dev llvm-16-dev libclang-16-dev
```
