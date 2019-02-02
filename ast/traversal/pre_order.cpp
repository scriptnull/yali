#include "traversal.h"
#include <stack>

namespace yali {
namespace ast {
namespace traversal {

void pre_order(AstNode* root, std::function<void(AstNode*)> callback) {
    if (root == nullptr)
        return;

    std::stack<AstNode*> st;
    st.push(root);

    while(!st.empty()) {
        auto curr = st.top();
        st.pop();

        callback(curr);

        for (auto it = curr->children.rbegin(); it != curr->children.rend(); ++it)
            st.push(*it);
    }
}

}
}
}