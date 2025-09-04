// Parser.h
#ifndef _parser_h_
#define _parser_h_

#include "Command.h"
#include "InputStream.h"
#include "OutputSink.h"
#include <string>
#include <vector>
#include <memory>

using namespace std;

// Info for redirection
struct RedirectionInfo {
    enum Type { NONE, INPUT, OUTPUT, OUTPUT_APPEND };
    Type type = NONE;
    string filename;
};

// Info for one command
struct CommandInfo {
    string command, option;
    vector<string> arguments;
    vector<bool> quotedArguments;
    RedirectionInfo inputRedirection;
    RedirectionInfo outputRedirection;
};

// Info for whole line
struct ParsedCommandLine {
    vector<CommandInfo> commands;
    bool isPipeline = false;
};

// Parses command strings
class Parser {
public:
    // Parser constructor
    Parser();
    // Parser destructor
    ~Parser();

    // Parse a command line
    ParsedCommandLine parse(const string& commandLine);

    // Create a command object
    shared_ptr<Command> createCommand(const CommandInfo& info);

private:
    // Helper parse functions
    string trim(const string& str);
    void validateCommandLine(const string& line);
    vector<string> tokenize(const string& str, vector<bool>& wasQuoted);
    RedirectionInfo findRedirection(const string& str, char op);
    CommandInfo parseCommand(const string& commandStr);
};

#endif