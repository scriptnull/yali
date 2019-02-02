#include "serializer.h"
#include "../traversal/traversal.h"
#include <iomanip>

namespace yali {
namespace ast {
namespace serializer {

std::ostream& MarkdownLevelTableSerializer::serialize(std::ostream& out, std::unique_ptr<yali::ast::AbstractSyntaxTree> const& tree) {

    out << "| " << "Level" << " | " << "Nodes" << " |" << std::endl;
    out << "|" << std::setfill('-') << std::setw(7) << "|" << std::setfill('-') << std::setw(7) << "|" << std::endl;

    yali::ast::traversal::level_order(tree->root,
        [&out](std::vector<yali::ast::AstNode*> level_nodes, int level) {
            out << "| " << level << " | ";
            for (auto node: level_nodes) {
                out << node->value << " ";                
            }
            out << "|" << std::endl;
        }
    );

    return out;
}

}
}
}