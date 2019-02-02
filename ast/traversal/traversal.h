#pragma once

#include "../ast.h"
#include <vector>
#include <functional>

namespace yali {
namespace ast {
namespace traversal {

void level_order(AstNode* root, std::function<void(AstNode*)> callback);
void level_order(AstNode* root, std::function<void(std::vector<AstNode*>, int)> callback);

void pre_order(AstNode* root, std::function<void(AstNode*)> callback);

void post_order(AstNode* root, std::function<void(AstNode*)> callback);

}
}
}
