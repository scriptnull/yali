#include "config.h"
#include "command.h"
#include "ast/ast.h"
#include "ast/traversal/traversal.h"
#include "ast/serializer/serializer.h"
#include <sstream>

namespace yali {
namespace app {

void AstCommand::run(Config* config) {
    std::vector<std::string> strs = {
        // // Expect 3
        // "(+ 1 2 )",

        // // Expect 3
        // "(+ 1 2)",

        // // Expect 3
        // "+ 1 2",

        // Expect 6
        "(+ 1 (+ 2 3))",

        // Expect 6
        // "(+ 1 2 3 )",

        // // Expect 6
        // "(+ 1 2 3)",

        // // Expect 6
        // "+ 1 2 3",

        // // Expect Unmatched Bracket Error
        // "+ 1 2 )",
    };

    for (auto s: strs) {
        try {
            std::istringstream ss{s};
            
            auto ast = yali::ast::parse(ss);

            yali::ast::serializer::MarkdownLevelTableSerializer fmt;

            fmt.serialize(std::cout, ast);
        } catch (std::runtime_error & e) {
            std::cerr << e.what() << std::endl;
        }
    }
}

}
}