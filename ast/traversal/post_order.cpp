#include "traversal.h"
#include <stack>

namespace yali {
namespace ast {
namespace traversal {

void post_order(AstNode* root, std::function<void(AstNode*)> callback) {
    if (root == nullptr)
        return;

    std::stack<AstNode*> st;
    std::stack<AstNode*> result;
    st.push(root);

    while(!st.empty()) {
        auto curr = st.top();
        st.pop();

        result.push(curr);

        for (auto child: curr->children)
            st.push(child);
    }

    while(!result.empty()) {
        auto curr = result.top();
        result.pop();

        callback(curr);
    }
}

}
}
}