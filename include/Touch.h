// Touch.h
#ifndef _touch_h_
#define _touch_h_

#include "Command.h"
#include <fstream>
#include <stdexcept>

// A command to create a new empty file
class Touch : public Command {
public:
    Touch();
    ~Touch();

    void execute() override;
    void validate() override;
};

#endif