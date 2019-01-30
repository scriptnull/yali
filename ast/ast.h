#pragma once

#include <string>
#include <vector>
#include <memory>
#include <iostream>

namespace yali {
namespace ast {

enum AstNodeType {
    Func,
    Data,
};

class AstNode {
public:
    std::vector<AstNode*> children;
    AstNodeType type;
    std::string value;

    AstNode(AstNodeType type, std::string value): type{type}, value{value} {}
};

std::ostream& operator<<(std::ostream& out, AstNode& node);

class AbstractSyntaxTree {
public:
    AstNode* root;

    AbstractSyntaxTree() {}
    ~AbstractSyntaxTree() {}
};

std::unique_ptr<AbstractSyntaxTree> parse(std::istream &);

}
}