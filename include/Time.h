// Time.h
#ifndef _time_h_
#define _time_h_

#include "Command.h"

// A command to display the current system time
class Time : public Command {
public:
    Time();
    virtual ~Time();
    virtual void execute() override;
    virtual void validate() override;
};

#endif