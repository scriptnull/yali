#include "traversal.h"
#include <queue>

namespace yali {
namespace ast {
namespace traversal {

void level_order(AstNode* root, std::function<void(AstNode*)> callback) {
    if (root == nullptr)
        return;

    std::queue<AstNode*> q;
    q.push(root);

    while(!q.empty()) {
        auto curr = q.front();
        q.pop();

        callback(curr);

        for (auto child: curr->children) {
            q.push(child);
        }
    }
}

void level_order(AstNode* root, std::function<void(std::vector<AstNode*>, int)> callback) {
    if (root == nullptr)
        return;

    std::queue<AstNode*> q;
    q.push(root);

    int level = 0;

    while(!q.empty()) {
        auto size = q.size();
        std::vector<AstNode*> level_nodes;
        level++;

        for (unsigned int i = 0; i < size; ++i) {
            auto curr = q.front();
            q.pop();

            level_nodes.push_back(curr);
            
            for (auto child: curr->children) {
                q.push(child);
            }
        }

        callback(level_nodes, level);
    }
}

}
}
}