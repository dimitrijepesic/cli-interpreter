// Parser.cpp
#include "Parser.h"
#include "Exceptions.h"
#include "Echo.h"
#include "Time.h"
#include "Date.h"
#include "Touch.h"
#include "Wc.h"
#include "Prompt.h"
#include "Truncate.h"
#include "Rm.h"
#include "Batch.h"
#include "Head.h"
#include "Tr.h"

#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <cctype>

using namespace std;

// Parser constructor
Parser::Parser() {}
// Parser destructor
Parser::~Parser() {}

// Remove whitespace
string Parser::trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == string::npos) return "";
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, last - first + 1);
}

// Check for valid char
static bool isWordChar(char c) {
    return isalnum(c) || c == '-' || c == '_' || c == '.' || c == '/' || c == '\\';
}

// Check for bad chars
void Parser::validateCommandLine(const string& line) {
    if (line.length() > 512) {
        throw LexicalException("Command line is too long, max 512 characters allowed");
    }

    string errorIndicators(line.length(), ' ');
    bool hasError = false;
    bool inQuotes = false;
    const string validOperators = "|<>";

    for (size_t i = 0; i < line.length(); ++i) {
        char c = line[i];
        if (c == '"') {
            if (!inQuotes && i > 0 && !isspace(line[i - 1]) && validOperators.find(line[i - 1]) == string::npos) {
                errorIndicators[i - 1] = '^'; hasError = true;
            }
            inQuotes = !inQuotes;
            continue;
        }
        if (inQuotes) continue;

        if (isWordChar(c) && i > 0 && line[i - 1] == '"') {
            errorIndicators[i] = '^'; hasError = true;
        }
        if (!isWordChar(c) && !isspace(c) && validOperators.find(c) == string::npos) {
            errorIndicators[i] = '^'; hasError = true;
        }
    }

    if (inQuotes) {
        throw SyntaxException("Unmatched quotes in command line");
    }
    if (hasError) {
        size_t lastChar = errorIndicators.find_last_not_of(' ');
        if (string::npos != lastChar) errorIndicators.resize(lastChar + 1);
        string errorMessage = "Error - unexpected characters or syntax error:\n";
        errorMessage += line + "\n" + errorIndicators;
        throw LexicalException(errorMessage);
    }
}

// Split by space, watch quotes
vector<string> Parser::tokenize(const string& str, vector<bool>& wasQuoted) {
    vector<string> tokens;
    wasQuoted.clear();
    string current;
    bool inQuotes = false;
    bool currentWasQuoted = false;

    for (size_t i = 0; i < str.length(); i++) {
        char c = str[i];
        if (c == '"') {
            inQuotes = !inQuotes;
            currentWasQuoted = true;
        }
        else if ((c == ' ' || c == '\t') && !inQuotes) {
            if (!current.empty()) {
                tokens.push_back(current);
                wasQuoted.push_back(currentWasQuoted);
                current.clear();
                currentWasQuoted = false;
            }
        }
        else {
            current += c;
        }
    }
    if (!current.empty()) {
        tokens.push_back(current);
        wasQuoted.push_back(currentWasQuoted);
    }
    return tokens;
}

// Find redirect file
RedirectionInfo Parser::findRedirection(const string& str, char op) {
    RedirectionInfo info;
    size_t pos = str.find(op);
    if (pos == string::npos) return info;

    if (op == '>' && pos + 1 < str.length() && str[pos + 1] == '>') {
        info.type = RedirectionInfo::OUTPUT_APPEND;
        pos++;
    }
    else if (op == '<') {
        info.type = RedirectionInfo::INPUT;
    }
    else if (op == '>') {
        info.type = RedirectionInfo::OUTPUT;
    }

    string rest = str.substr(pos + 1);
    rest = trim(rest);
    if (rest.empty()) {
        throw SyntaxException("Missing filename for redirection");
    }

    size_t end = rest.find_first_of(" \t");
    info.filename = (end != string::npos) ? rest.substr(0, end) : rest;
    return info;
}

// Parse one command part
CommandInfo Parser::parseCommand(const string& commandStr) {
    CommandInfo info;
    string cleanCommand = commandStr;

    auto inputRedir = findRedirection(commandStr, '<');
    if (inputRedir.type != RedirectionInfo::NONE) {
        info.inputRedirection = inputRedir;
        cleanCommand = cleanCommand.substr(0, cleanCommand.find('<'));
    }

    auto outputRedir = findRedirection(commandStr, '>');
    if (outputRedir.type != RedirectionInfo::NONE) {
        info.outputRedirection = outputRedir;
        cleanCommand = cleanCommand.substr(0, cleanCommand.find('>'));
    }

    vector<bool> wasQuoted;
    auto tokens = tokenize(cleanCommand, wasQuoted);
    if (tokens.empty()) throw runtime_error("Empty command");

    info.command = tokens[0];
    for (size_t i = 1; i < tokens.size(); i++) {
        if (tokens[i].size() > 1 && tokens[i][0] == '-' && info.option.empty()) {
            info.option = tokens[i];
        }
        else {
            info.arguments.push_back(tokens[i]);
            info.quotedArguments.push_back(wasQuoted[i]);
        }
    }
    return info;
}

// Parse the whole line
ParsedCommandLine Parser::parse(const string& commandLine) {
    validateCommandLine(commandLine);
    ParsedCommandLine result;
    string current;
    bool inQuotes = false;
    vector<string> segments;

    for (char c : commandLine) {
        if (c == '"') {
            inQuotes = !inQuotes;
            current += c;
        }
        else if (c == '|' && !inQuotes) {
            segments.push_back(trim(current));
            current.clear();
            result.isPipeline = true;
        }
        else {
            current += c;
        }
    }
    if (!current.empty()) segments.push_back(trim(current));

    for (const string& segment : segments) {
        result.commands.push_back(parseCommand(segment));
    }

    // Check for bad redirection in pipeline
    if (result.isPipeline) {
        for (size_t i = 0; i < result.commands.size(); i++) {
            if (i > 0 && result.commands[i].inputRedirection.type != RedirectionInfo::NONE) {
                throw SemanticException("Input redirection is not allowed in a pipeline");
            }
            if (i < result.commands.size() - 1 && result.commands[i].outputRedirection.type != RedirectionInfo::NONE) {
                throw SemanticException("Output redirection is not allowed in a pipeline");
            }
        }
    }
    return result;
}

// Create command from info
shared_ptr<Command> Parser::createCommand(const CommandInfo& info) {
    shared_ptr<Command> cmd;

    if (info.command == "echo") {
        cmd = make_shared<Echo>();
    }
    else if (info.command == "time") {
        cmd = make_shared<Time>();
    }
    else if (info.command == "date") {
        cmd = make_shared<Date>();
    }
    else if (info.command == "touch") {
        cmd = make_shared<Touch>();
    }
    else if (info.command == "wc") {
        cmd = make_shared<Wc>();
    }
    else if (info.command == "prompt") {
        cmd = make_shared<Prompt>();
    }
    else if (info.command == "truncate") {
        cmd = make_shared<Truncate>();
    }
    else if (info.command == "rm") {
        cmd = make_shared<Rm>();
    }
    else if (info.command == "batch") {
        cmd = make_shared<Batch>();
    }
    else if (info.command == "head") {
        cmd = make_shared<Head>();
    }
    else if (info.command == "tr") {
        auto trCmd = make_shared<Tr>();
        if (info.arguments.size() >= 1) {
            trCmd->setWhat(info.arguments[0]);
        }
        if (info.arguments.size() >= 2) {
            trCmd->setWith(info.arguments[1]);
        }
        cmd = trCmd;
    }
    else {
        throw UnknownCommandException("Unknown command: " + info.command);
    }

    // Set options and arguments
    cmd->setOption(info.option);
    cmd->setArguments(info.arguments);

    if (!info.arguments.empty() && !info.quotedArguments.empty()) {
        cmd->setQuotedArgument(info.quotedArguments[0]);
    }

    return cmd;
}