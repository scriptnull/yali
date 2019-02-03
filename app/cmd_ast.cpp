#include "config.h"
#include "command.h"
#include "ast/ast.h"
#include "ast/traversal/traversal.h"
#include "ast/serializer/serializer.h"
#include <sstream>

namespace yali {
namespace app {

void AstCommand::run(Config* config) {
    while (true) {
        std::cout << "> ";
        
        std::string src;
        std::getline(std::cin, src);

        if (src == "exit" || src == "(exit)")
            break;

        std::istringstream ss{src};
        handle_input(ss);
    }
}

void AstCommand::handle_input(std::istream& stream) {
    try {
        auto ast = yali::ast::parse(stream);

        yali::ast::serializer::ArraySquareSerializer fmt;

        fmt.serialize(std::cout, ast);

    } catch (std::runtime_error & e) {
        std::cerr << e.what() << std::endl;
    }
}

}
}