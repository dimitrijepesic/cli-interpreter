// Truncate.h
#ifndef _truncate_h_
#define _truncate_h_

#include "Command.h"
#include <fstream>
#include <stdexcept>

// A command to empty a certain file
class Truncate : public Command {
public:
    Truncate();
    ~Truncate();

    void execute() override;
    void validate() override;
};

#endif