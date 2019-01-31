#include "ast.h"
#include <exception>
#include <unordered_map>

namespace yali {
namespace ast {

std::ostream& operator<<(std::ostream& out, AstNode* node) {
    std::cout << "!----!" << std::endl;
    std::cout << "Value = " << node->value << std::endl;

    std::cout << "NodeType = ";
    switch (node->type) {
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

    std::stack<AstNode*> call_stack;
    std::stack<SymType> sym_stack;

    sym_stack.push(blank);

    char c;
    char prev;
    AstNode* curr = nullptr;
    while (true) {
        stream.get(c);
        
        std::cout << "c = " << c << " goes to ";

        switch (sym_stack.top()) {
            case blank:
                std::cout << "inside blank" << std::endl;

                if (c == '(') {
                    sym_stack.push(open_brac);
                    break;
                }
                
                // fallthrough
            case open_brac:
                std::cout << "inside open_brac" << std::endl;
                
                if (curr == nullptr) {
                    curr = new AstNode{AstNodeType::Func, std::string{c}};
                    if (ast->root == nullptr)
                        ast->root = curr;
                    break;
                }

                if (c == ' ') {
                    call_stack.push(curr);
                    sym_stack.push(func_name);
                    curr = nullptr;
                    break;
                }

                curr->value += c;
                break;
            case close_brac:
                std::cout << "inside close_brac" << std::endl;

                // Remove symbols till matching bracket
                while (!sym_stack.empty() && (sym_stack.top() != open_brac)) {
                    sym_stack.pop();
                }

                // Remove open_brac
                if (!sym_stack.empty())
                    sym_stack.pop();

                // print_stack<SymType>("sym_table", sym_stack);
                // print_stack<AstNode*>("call_stack", call_stack);

                if (call_stack.size() >= 2) {
                    auto child = call_stack.top();
                    call_stack.pop();

                    auto parent = call_stack.top();
                    parent->children.push_back(child);
                }

                // print_stack<SymType>("sym_table", sym_stack);
                // print_stack<AstNode*>("call_stack", call_stack);

                break;
            case func_name:
                std::cout << "inside func_name" << std::endl;
                
                if (curr == nullptr) {
                    curr = new AstNode{AstNodeType::Data, std::string{c}};
                    break;
                }

                if (c == ' ') {
                    auto caller = call_stack.top();
                    caller->children.push_back(curr);
                    sym_stack.push(func_arg);
                    curr = nullptr;
                    break;
                }
                
                curr->value += c;
                break;
            case func_arg:
                std::cout << "inside func_arg" << std::endl;
                
                if (c == '(') {
                    sym_stack.push(open_brac);
                    curr = nullptr;
                    break;
                }

                if (c == ')') {
                    if (curr != nullptr) {
                        auto caller = call_stack.top();
                        caller->children.push_back(curr);
                        sym_stack.push(close_brac);
                        curr = nullptr;
                    }
                    break;
                }

                if (curr == nullptr) {
                    curr = new AstNode{AstNodeType::Data, std::string{c}};
                    break;
                }

                if (stream.eof()) {
                    if (prev == ' ' || prev == ')')
                        break;

                    auto caller = call_stack.top();
                    caller->children.push_back(curr);
                    curr = nullptr;
                    break;
                }

                if (c == ' ') {
                    auto caller = call_stack.top();
                    caller->children.push_back(curr);
                    sym_stack.push(func_arg);
                    curr = nullptr;
                    break;
                }

                curr->value += c;
                break;
        }

        prev = c;

        if (stream.eof())
            break;
    }

    print_stack<SymType>("sym_table", sym_stack);
    print_stack<AstNode*>("call_stack", call_stack);

    return ast;
}

template <typename T> void print_stack(std::string msg, std::stack<T> & st) {
    std::stack<T> backup;
    std::cout << msg << std::endl;
    std::cout << "*********" << std::endl;
    while(!st.empty()) {
        std::cout << st.top() << std::endl;
        std::cout << "----------" << std::endl;
        backup.push(st.top());
        st.pop();
    }

    while(!backup.empty()) {
        st.push(backup.top());
        backup.pop();
    }
    std::cout << "*********" << std::endl;
}

}
}