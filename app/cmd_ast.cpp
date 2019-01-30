#include "config.h"
#include "command.h"
#include "ast/ast.h"
#include "ast/traversal/traversal.h"
#include <sstream>

namespace yali {
namespace app {

void AstCommand::run(Config* config) {
    std::cout << "Building Abstact Syntax Tree" << std::endl;

    std::vector<std::string> strs = {
        // Expect 3
        "(+ 1 2 )",

        // Expect 3
        "(+ 1 2)",

        // // Expect 3
        // "+ 1 2",

        // // Expect Unmatched Bracket Error
        // "+ 1 2 )",
    };

    for (auto s: strs) {
        try {
            std::istringstream ss{s};
            
            auto ast = yali::ast::parse(ss);

            std::cout << "ast for " << s << std::endl;
            yali::ast::traversal::level_order(ast->root, [](yali::ast::AstNode* node) {
                std::cout << *node;
            });
        } catch (std::runtime_error & e) {
            std::cerr << e.what() << std::endl;
        }
    }

    std::cout << "AST built successfully" << std::endl;
}

}
}