// Rm.h
#ifndef _rm_h_
#define _rm_h_

#include "Command.h"
#include <cstdio>
#include <stdexcept>

// A command to delete a file
class Rm : public Command {
public:
    Rm();
    ~Rm();

    void execute() override;
    void validate() override;
};

#endif