#include "app.h"

namespace yali {
namespace app {

void Application::run() {
    _command->run(_config);
}

Application::~Application() {
    delete _command;
    delete _config;
}

CommandType get_command_type(const std::string cmd) {
    if (cmd == "ast")
        return Ast;

    return Help;
}

std::unique_ptr<Application> create(int argc, char* argv[]) {
    Config* config = new Config;
    Command* command = new HelpCommand;

    if (argc < 2)
        return std::unique_ptr<Application>(new Application {config, command});

    const std::string arg_cmd{argv[1]};
    auto cmd = get_command_type(arg_cmd);

    switch (cmd) {
       case Ast:
            command = new AstCommand;
            break;
        case Help:
            command = new HelpCommand;
            break;
    }

    return std::unique_ptr<Application>(new Application {config, command});
}

}
}