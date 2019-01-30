#pragma once

#include "../ast.h"
#include <functional>

namespace yali {
namespace ast {
namespace traversal {

void level_order(AstNode* node, std::function<void(AstNode*)> callback);

}
}
}
