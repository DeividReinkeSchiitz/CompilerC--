# CMM Compiler

This project is a compiler for a simple programming language called C-- (Cmm). The compiler is implemented in C++ and includes a scanner, parser, and token management. 

The compiler only makes the syntactic and lexical analysis.
## Project Structure

### Files and Directories

- .clang-format: Clang format configuration file.
- .gitignore: Git ignore file.
- Examples/: Directory containing example CMM files.
- main.cpp: Main entry point of the compiler.
- parser.cpp, parser.h: Implementation of the parser.
- scanner.cpp, scanner.h: Implementation of the scanner.
- token.h: Definition of the Token class and related enums..

## Usage

To compile the project, use the following command:

```sh
g++ -o compiler *.cpp
```

## To run the compiler, use the following command:
```sh
./compiler <filename>.cmm
```

### Example
```sh
g++ -o compiler *.cpp

./compiler Examples/ex1.cmm
```