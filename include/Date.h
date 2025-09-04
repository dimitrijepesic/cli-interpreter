// Date.h
#ifndef _date_h_
#define _date_h_

#include "Command.h"
#include <ctime>
#include <iomanip>

// A command to print date
class Date : public Command {
public:
    Date();
    ~Date();

    void execute() override;
    void validate() override;
};

#endif