// Command.h
#ifndef _command_h_
#define _command_h_

#include "InputStream.h"
#include "OutputSink.h"
#include "Exceptions.h"
#include <string>
#include <vector>
#include <memory>

using namespace std;

// Base class for all commands
class Command {
protected:
    
    // Command option like -n
    string option; 
    // Command arguments
    vector<string> arguments; 
    // If first arg was quoted
    bool firstArgumentQuoted = false; 

    // Input stream for command
    shared_ptr<InputStream> input; 
    // Output sink for command
    shared_ptr<OutputSink> output; 

public:

    Command();
    virtual ~Command();

	// Setters for parameters of the command
    void setOption(const string& opt) { option = opt; }
    void setArguments(const vector<string>& args) { arguments = args; }
    void setQuotedArgument(bool quoted) { firstArgumentQuoted = quoted; }

    // Setters for streams
    void setInputStream(shared_ptr<InputStream> in) { this->input = in; }
    void setOutputSink(shared_ptr<OutputSink> out) { this->output = out; }

    // Main command function
    virtual void execute() = 0;

    // Validate command syntax
    virtual void validate() {}

protected:
    // Read from input
    string readInput();
    // Write to output
    void writeOutput(const string& data);
};

#endif