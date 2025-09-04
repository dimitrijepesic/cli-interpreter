// Echo.h
#ifndef _echo_h_
#define _echo_h_

#include "Command.h"

// A command to print arguments or input stream
class Echo : public Command {
public:
    Echo();
    virtual ~Echo();

    virtual void execute() override;
    virtual void validate() override;
};

#endif