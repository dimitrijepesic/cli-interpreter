// Batch.h

#include "Batch.h"
#include "CLI.h"
#include "Exceptions.h"

#include <sstream>
#include <fstream>
#include <string>
#include <iostream>

// Constructor
Batch::Batch() {}
// Destructor
Batch::~Batch() {}

static inline std::string trimCopy(const std::string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) return "";
    size_t end = s.find_last_not_of(" \t\r\n");
    return s.substr(start, end - start + 1);
}

void Batch::execute() {
    string content;

    // First case: normal read from file
    if (!arguments.empty()) {
        ifstream file(arguments[0]);
        if (!file) {
            throw ExecutionException("batch: cannot open file '" + arguments[0] + "'");
        }
        stringstream buffer;
        buffer << file.rdbuf();
        content = buffer.str();
    }
    else {
        content = readInput();
    }

    // Creates an input stream from the content
    istringstream iss(content);
    string line;
    auto cli = CLI::singleton();

    // Goes through each line of the input and executes it
    while (getline(iss, line)) {
        // Treat '^Z' (two characters) OR ASCII 26 as EOF
        const string trimmed = trimCopy(line);
        if (trimmed == "^Z" || trimmed.find('\x1A') != string::npos) {
            break;
        }

        if (!trimmed.empty()) {
            try {
                cli->execute(trimmed);
            }
            catch (const exception& e) {
                writeOutput("Error in batch script: " + string(e.what()) + "\n");
            }
        }
    }
}

// Validates if the command is used correctly
void Batch::validate() {

    // Enough arguments
    if (arguments.size() > 1) {
        throw SemanticException("batch: takes at most one file argument");
    }
    // No options allowed
    if (!option.empty()) {
        throw SemanticException("batch: does not take any options");
    }
}
