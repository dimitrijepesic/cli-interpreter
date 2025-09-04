#include "Tr.h"
#include "Exceptions.h"

#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

// Constructor
Tr::Tr() {}
// Destructor
Tr::~Tr() {}

// Helper to replace text
static void replaceAll(string& s, const string& what, const string& with) {
    for (size_t pos = 0; (pos = s.find(what, pos)) != string::npos; pos += with.length()) {
        s.replace(pos, what.length(), with);
    }
}

// Run the replace logic
void Tr::execute() {
    string text;
    string what_arg;
    string with_arg = "";

    // Case for 3 arguments
    if (arguments.size() == 3) {
        what_arg = arguments[1];
        with_arg = arguments[2];

        // Check if source is string or file
        if (firstArgumentQuoted) {
            // Handle quoted string
            text = arguments[0];
        }
        else {
            // Handle filename
            ifstream file(arguments[0]);
            if (!file) {
                throw ExecutionException("tr: cannot open file '" + arguments[0] + "'");
            }
            stringstream buffer;
            buffer << file.rdbuf();
            text = buffer.str();
        }
    }
    // Case for 1 or 2 arguments
    else {
        // Get text from pipe
        text = readInput();
        what_arg = arguments[0];
        if (arguments.size() == 2) {
            with_arg = arguments[1];
        }
    }

    // Do the replacement
    replaceAll(text, what_arg, with_arg);
    // Print the result
    writeOutput(text);
}

// Validate tr arguments
void Tr::validate() {
    if (arguments.size() < 1 || arguments.size() > 3) {
        throw SemanticException("tr: requires one, two, or three arguments");
    }
    if (!option.empty()) {
        throw SemanticException("tr: does not take any options");
    }
}