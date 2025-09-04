// Tr.h
#ifndef _tr_h_
#define _tr_h_

#include "Command.h"
#include <string>

// A command to replace characters
class Tr : public Command {
public:

    Tr();
	~Tr();

    void execute() override;
    void validate() override;

    // Setters used by the parser for arguments with and what
    void setWhat(const std::string& w) { what = w; }
    void setWith(const std::string& w) { with = w; }
    void setInput(const std::string& s) { input = s; }

private:
    std::string what;
    std::string with;
    std::string input;
};

#endif