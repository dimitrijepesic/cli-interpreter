// Batch.h
#ifndef _batch_h
#define _batch_h

#include "Command.h"
#include "CLI.h"
#include <sstream>
#include <iostream>

// Command to run commands from file
class Batch : public Command {
public:
    Batch();
    ~Batch();

    void execute() override;
    void validate() override;
};

#endif