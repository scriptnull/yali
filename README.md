# yali

> Yet Another Lisp

## Goals
1. Embeddable Lisp Interpreter.
1. Tool for learning (about Lisp, ASTs, Dialects, etc.)
1. Multiple Lisp Dialect support.
1. Modular API with documentation.

## Requirements

1. Unix-based machine (currently most dev happens on Ubuntu 16.04)
1. [bazel](https://bazel.build/) (build tool)
1. GCC Compiler (5.4.0)
1. GNU Make 4.1

Option Dev Dependencies:
1. graphviz + xdot (if you want to visualize build graph)
    ```bash
    sudo apt update && sudo apt install graphviz xdot
    ```
