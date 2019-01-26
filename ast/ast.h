#pragma once

#include <string>

namespace yali {
namespace ast {

enum AstNodeType {
    Func,
    Data,
};

class AstNode {
public:
    AstNode* left;
    AstNode* right;
    AstNodeType type;
};

class AbstractSyntaxTree {
public:
    AstNode* root;

    AbstractSyntaxTree();
    ~AbstractSyntaxTree();
};

AbstractSyntaxTree* parse(std::string);

}
}