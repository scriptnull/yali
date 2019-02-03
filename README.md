# yali

> Yet Another Lisp

![license](https://img.shields.io/github/license/scriptnull/yali.svg?style=flat-square) [![first-timers-only](https://img.shields.io/badge/first--timers--only-friendly-blue.svg?style=flat-square)](https://www.firsttimersonly.com/)

## Goals
1. Embeddable Lisp Parser.
1. Tool for learning (about Lisp, ASTs, Dialects, etc.)
1. Modular API with documentation.

Eventual goals:
1. Multiple Lisp Dialect support.
1. Plug and play Interpreters.

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

## AST Serializers
Yali aims to be a tool to learn about Lisp and ASTs. Hence it provides serializers that output AST in different form.

### Graphviz

`(+ 4 (- 6 5) (+ 2 3))` translates to graphviz language

```
digraph G { 
    1[label="+"]
    2[label="4"]
    3[label="-"]
    4[label="6"]
    5[label="5"]
    6[label="+"]
    7[label="2"]
    8[label="3"]
    1 -> 2
    1 -> 3
    1 -> 6
    3 -> 4
    3 -> 5
    6 -> 7
    6 -> 8
}
```

which could be used with tools like [Webgraphviz](http://www.webgraphviz.com/) to get a graphic like

![image](https://user-images.githubusercontent.com/4211715/52170132-a8971100-276a-11e9-8ef3-b4cfdb494fb6.png)

### Markdown Level Table
`(+ 4 (- 6 5) (+ 2 3))` translates to markdown table

```
| Level | Nodes |
|------|------|
| 1 | + |
| 2 | 4 - + |
| 3 | 6 5 2 3 |
```

which renders on Markdown documents like

| Level | Nodes |
|------|------|
| 1 | + |
| 2 | 4 - + |
| 3 | 6 5 2 3 |

### Array Square
Preferred often for [lightweight parsers](http://norvig.com/lispy.html).

`(+ 4 (- 6 5) (+ 2 3))` translates to `[+, 4, [-, 6, 5], [+, 2, 3]]`

## Contributing
Yes, please!

- Suggest features and report bugs on the [issue tracker](https://github.com/scriptnull/yali/issues)
- Refactor code to remove memory leaks
- Write more tests
- Code review to help improve the existing code

If you need help, feel free to contact [me](https://vishnubharathi.codes/).

## License

MIT License - see [`LICENSE`](LICENSE) for more details
