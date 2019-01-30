#include "ast.h"
#include <stack>
#include <exception>
#include <unordered_map>

namespace yali {
namespace ast {

std::ostream& operator<<(std::ostream& out, AstNode& node) {
    std::cout << "!----!" << std::endl;
    std::cout << "Value = " << node.value << std::endl;

    std::cout << "NodeType = ";
    switch (node.type) {
        case AstNodeType::Func:
            std::cout << "Func" << std::endl;
            break;
        case AstNodeType::Data:
            std::cout << "Data" << std::endl;
            break;
    }
    std::cout << "!----!" << std::endl;

    return out;
}

enum SymType {
    blank,
    open_brac,
    close_brac,
    func_name,
    func_arg
};

std::ostream& operator<<(std::ostream& out, yali::ast::SymType t) {
    switch (t)
    {
        case blank:
            out << "blank";
            break;
        case open_brac:
            out << "open_brac";
            break;
        case close_brac:
            out << "close_brac";
            break;
        case func_name:
            out << "func_name";
            break;
        case func_arg:
            out << "func_arg";
            break;
    }
    return out;
}

class operation {
};

class SymTable {
private:
    std::unordered_map<std::string, operation*> table;
public:
    SymTable() {
        table.insert(std::pair<std::string, operation*>("+", nullptr));
        table.insert(std::pair<std::string, operation*>("-", nullptr));
    }
    SymTable(SymTable const &) = delete;
    void operator=(SymTable const &) = delete;

    bool has_func(std::string func_name) const {
        return table.find(func_name) != table.end();
    }
};

template <class T>
class Singleton {
public:
    static const T & instance() {
        static T* inst = new T();
        return *inst;
    }
};

typedef Singleton<SymTable> SymbolTable;

std::unique_ptr<AbstractSyntaxTree> parse(std::istream & stream) {
    std::unique_ptr<AbstractSyntaxTree> ast{new AbstractSyntaxTree};

    char c;
    std::string curr_func;
    std::string curr_arg;
    SymType last_symbol = SymType::blank;

    std::stack<char> src_stack;

    AstNode* curr_node;

    while (stream.get(c)) {
        switch (c) {
            case '(':
                src_stack.push(c);
                curr_func = "";
                last_symbol = SymType::open_brac;
                break;
            case ')':
                if (src_stack.empty() || src_stack.top() != '(')
                    throw std::runtime_error("Invalid Syntax: Could not find matching braces");
                src_stack.pop();

                if (last_symbol == func_name || last_symbol == func_arg) {
                    AstNode* arg_node = new AstNode{AstNodeType::Data, curr_arg};
                    curr_node->children.push_back(arg_node);
                    curr_arg = "";
                }

                last_symbol = SymType::close_brac;
                break;
            default:
                std::cout << 
                    "c = " << c << "\n" <<
                    "curr_func = " << curr_func << "\n" <<
                    "curr_arg = " << curr_arg << "\n" <<
                    "last_symbol = " << last_symbol << "\n";

                if (last_symbol == SymType::blank || last_symbol == SymType::open_brac) {
                    if (c != ' ') {
                        curr_func += c;
                        break;
                    } else {
                        // check if func exists 
                        if (SymbolTable::instance().has_func(curr_func)) {
                            AstNode* node = new AstNode{AstNodeType::Func, curr_func};

                            if (ast->root == nullptr) {
                                ast->root = node;
                                curr_node = node;
                            }

                            last_symbol = SymType::func_name;
                        }
                    }
                } else if (last_symbol == SymType::func_name || last_symbol == SymType::func_arg) {
                    if (c != ' ') {
                        curr_arg += c;
                        break;
                    } else {
                        AstNode* arg_node = new AstNode{AstNodeType::Data, curr_arg};
                        curr_node->children.push_back(arg_node);

                        last_symbol = SymType::func_arg;
                        curr_arg = "";
                    }
                }
        }
    }

    return ast;
}

}
}