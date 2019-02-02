#include "serializer.h"
#include "../traversal/traversal.h"
#include <unordered_map>

namespace yali {
namespace ast {
namespace serializer {

std::ostream& GraphvizSerializer::serialize(std::ostream& out, std::unique_ptr<yali::ast::AbstractSyntaxTree> const& tree) {
    
    out << "digraph G { " << std::endl;

    int node_num = 0;

    std::unordered_map<AstNode*,int> map;

    yali::ast::traversal::pre_order(tree->root, [&out, &node_num, &map](AstNode* node) {
        out << "    " << ++node_num << "[label=\"" << node->value << "\"]" << std::endl;

        map.insert(std::pair<AstNode*,int> {node, node_num});
    });

    yali::ast::traversal::pre_order(tree->root, [&out, &node_num, &map](AstNode* node) {
        auto parent_num = map.at(node);

        for (auto child: node->children) {
            auto child_num = map.at(child);

            out << "    " << parent_num << " -> " << child_num << std::endl;
        }
    });

    out << "}" << std::endl;

    return out;
}

}
}
}