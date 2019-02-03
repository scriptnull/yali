#pragma once

namespace yali {
namespace app {

class Command {
public:
    virtual void run(Config* config) = 0;  
    virtual ~Command() = default; 
};

class HelpCommand : public Command {
public:
    void run(Config* config) override;
};

class AstCommand : public Command {
public:
    void run(Config* config) override;
    void handle_input(std::istream&);
};

}
}