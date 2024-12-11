# CMM Compiler

This project is a compiler for a simple programming language called C-- (Cmm). The compiler is implemented in C++ and includes a scanner, parser, and token management. 

The compiler only makes the syntactic and lexical analysis.


## Grammar of G-- 
The following grammar uses the notation \((N)^*\) to represent 0 or more repetitions of \(N\) and the notation \((N)?\) to represent 0 or 1 repetition of \(N\). The tokens of the language are represented in <span style="color:red">red</span> and the nonterminals in <i>italic</i>.


1. <i>Program</i> → (<i>Function</i>)<sup>*</sup> <span style="color:red">EOF</span>  
2. <i>Function</i> → <i>Type</i> <span style="color:red">ID(</span> <i>ParamTypes</i> <span style="color:red">) { (</span> <i>Type VarDeclaration</i> (<span style="color:red">,</span> <i>VarDeclaration</i>)<sup>*</sup> <span style="color:red">;</span> )<sup>*</sup> (<i>Statement</i>)<sup>*</sup> <span style="color:red">}</span>  
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;| <span style="color:red">void ID(</span> <i>ParamTypes</i> <span style="color:red">) { (</span> <i>Type VarDeclaration</i> (<span style="color:red">,</span> <i>VarDeclaration</i>)<sup>*</sup> <span style="color:red">;</span> )<sup>*</sup> (<i>Statement</i>)<sup>*</sup> <span style="color:red">}</span>  

3. <i>VarDeclaration</i> → <span style="color:red">ID </span>(<span style="color:red">[ <i>integerconstant</i> ]</span>)?</span>  

4. <i>Type</i> → <span style="color:red">char</span>  
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;| <span style="color:red">int</span>  

5. <i>ParamTypes</i> → <span style="color:red">void</span>  
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;| <i>Type <span style="color:red">ID(</span><span style="color:red">[]</span>)?</i> (<span style="color:red">,</span> <i>Type <span style="color:red">ID</span>(<span style="color:red">[]</span>)?</i>)<sup>*</sup>  

6. <i>Statement</i> → <span style="color:red">if (</span> <i>Expression</i> <span style="color:red">)</span> <i>Statement</i> (<span style="color:red">else</span> <i>Statement</i>)?  
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;| <span style="color:red">while (</span> <i>Expression</i> <span style="color:red">)</span> <i>Statement</i>  
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;| <span style="color:red">for (</span> (<i>Assign</i>? <span style="color:red">;</span> <i>Expression</i>? <span style="color:red">;</span> <i>Assign</i>?) <span style="color:red">)</span> <i>Statement</i>  
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;| <span style="color:red">return </span>( <i>Expression</i> )?<span style="color:red">;</span>  
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;| <i>Assign</i> <span style="color:red">;</span>  
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;| <span style="color:red">ID((</span> <i>Expression</i> (<span style="color:red">,</span> <i>Expression</i>)<sup>*</sup> <span style="color:red">)?) ;</span>  
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;| <span style="color:red">{ (</span> <i>Statement</i><sup>*</sup> <span style="color:red">) }</span>  
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;| <span style="color:red">;</span>  

7. <i>Assign</i> → <span style="color:red">ID </span>(<span style="color:red">[</span> <i>Expression</i> <span style="color:red">]</span>)? <span style="color:red">=</span> <i>Expression</i>  

8. <i>Expression</i> → <span style="color:red">-</span> <i>Expression</i>  
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;| <span style="color:red">!</span> <i>Expression</i>  
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;| <i>Expression <span style="color:red">BinOp</span> Expression</i>  
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;| <i>Expression <span style="color:red">RelOp</span> Expression</i>  
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;| <i>Expression <span style="color:red">LogOp</span> Expression</i>  
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;| <span style="color:red">ID((</span> <i>Expression</i> (<span style="color:red">,</span> <i>Expression</i>)<sup>*</sup> <span style="color:red">)?) | [</span> <i>Expression</i> <span style="color:red">])?</span>  
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;| <span style="color:red">(</span> <i>Expression</i> <span style="color:red">)</span>  
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;| <span style="color:red">integerconstant</span>  
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;| <span style="color:red">charconstant</span>  
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;| <span style="color:red">stringconstant</span>  

9. <i>BinOp</i> → <span style="color:red">+</span>  
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;| <span style="color:red">-</span>  
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;| <span style="color:red">*</span>  
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;| <span style="color:red">/</span>  

10. <i>RelOp</i> → <span style="color:red">==</span>  
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;| <span style="color:red">!=</span>  
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;| <span style="color:red"><=</span>  
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;| <span style="color:red"><</span>  
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;| <span style="color:red">>=</span>  
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;| <span style="color:red">></span>  

11. <i>LogOp</i> → <span style="color:red">&amp;&amp;</span>  
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;| <span style="color:red">||</span>

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