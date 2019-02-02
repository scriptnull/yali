#include "serializer.h"
#include "../traversal/traversal.h"
#include <unordered_map>

namespace yali {
namespace ast {
namespace serializer {

std::ostream& ArraySquareSerializer::serialize(std::ostream& out, std::unique_ptr<yali::ast::AbstractSyntaxTree> const& tree) {
    
    std::unordered_map<AstNode*, std::string> rep_map;

    yali::ast::traversal::post_order(tree->root, [&out, &rep_map](AstNode* node) {
        std::string rep = "";
        switch(node->type) {
            case Data:
                rep += node->value;
                break;
            case Func:
                rep += "[" + node->value + ", ";
                for (auto child: node->children) {
                    rep += rep_map.at(child);

                    if (child != node->children.back())
                        rep += ", ";
                }
                rep += "]";
        }
        rep_map[node] = rep;
    });

    out << rep_map.at(tree->root) << std::endl;

    return out;
}

}
}
}