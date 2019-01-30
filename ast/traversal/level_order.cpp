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

    int total_nodes = 0;

    while(!q.empty()) {
        auto curr = q.front();
        q.pop();

        callback(curr);
        total_nodes++;

        for (auto child: curr->children) {
            q.push(child);
        }
    }

    std::cout << "total nodes = " << total_nodes << std::endl;
}

}
}
}