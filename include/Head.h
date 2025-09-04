// Head.h
#ifndef _head_h_
#define _head_h_

#include "Command.h"
#include <string>

// Display the first few lines of a text
class Head : public Command {
private:
    // Number of lines to print
    int count = 0;

public:
    Head();
    virtual ~Head();

    void execute() override;
    void validate() override;
};

#endif