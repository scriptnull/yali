#include <iostream>
#include "config.h"
#include "command.h"

namespace yali {
namespace app {

void HelpCommand::run(Config* config) {
    std::cout << "\nUsage: yali command [options] \n\n";
    std::cout << "Commands:" << std::endl;
    std::cout << "  ast [filename] - Prints the Abstract Syntax Tree" << std::endl;
}

}
}