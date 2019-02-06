#include <iostream>
#include <memory>
#include <stack>
#include "ast/ast.h"

namespace yali {
namespace parser {

enum SymType {
    blank,
    open_brac,
    close_brac,
    func_name,
    func_arg
};

class State {
public:
};

class blank {
private:
    Parser* _parser;
public:
    blank(Parser* parser): _parser{parser} {};
};

class open_brac {
private:
    Parser* _parser;
public:
    open_brac(Parser* parser): _parser{parser} {};
};

class func_name {
private:
    Parser* _parser;
public:
    func_name(Parser* parser): _parser{parser} {};
};

class func_arg {
private:
    Parser* _parser;
public:
    func_arg(Parser* parser): _parser{parser} {};
};

class close_brac {
private:
    Parser* _parser;
public:
    close_brac(Parser* parser): _parser{parser} {}; 
};

class eof {
private:
    Parser* _parser;
public:
    eof(Parser* parser): _parser{parser} {};
};

class Parser {
private:
    State* blank;
    State* open_brac;
    State* func_name;
    State* func_arg;
    State* close_brac;
    State* eof;

    State* state;

    std::istream& stream;
    char current_character;
    std::stack<yali::ast::AstNode*> call_stack;
    std::stack<SymType> sym_stack;
    yali::ast::AbstractSyntaxTree ast;
public:
    Parser(std::istream& _stream);

    std::unique_ptr<yali::ast::AbstractSyntaxTree> parse();
};

}
}