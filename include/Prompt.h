// Prompt.h
#ifndef _prompt_h_
#define _prompt_h_

#include "Command.h"
#include "CLI.h"
#include <string>
#include <memory>
#include <stdexcept>

// A command to change the CLI prompt
class Prompt : public Command {
public:
    Prompt();
    ~Prompt();

    void execute() override;
    void validate() override;
};

#endif