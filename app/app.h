#pragma once

#include <string>
#include <memory>
#include <vector>
#include "config.h"
#include "command.h"

namespace yali {
namespace app {

class Application {
private:
    Config* _config;
    Command* _command;
public:
    Application(Config* config, Command* command): _config(config), _command(command) {}

    void run();

    ~Application();
};

enum CommandType {
    Ast,
    Help
};

CommandType get_command_type(const std::string cmd);
std::unique_ptr<Application> create(int argc, char* argv[]);

}
}