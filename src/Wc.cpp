#include "Wc.h"
#include "Exceptions.h"
#include <stdexcept>
#include <sstream>
#include <fstream>

using namespace std;

// Constructor
Wc::Wc() {}
// Destructor
Wc::~Wc() {}

// Counts words or characters from a file, string, or pipe
void Wc::execute() {
    string data;
    // Find the source of data
    if (!arguments.empty()) {
        // If the argument was quoted, direct text input
        if (firstArgumentQuoted) {
            data = arguments[0];
        }
        // Else, treat it as a filename
        else {
            ifstream file(arguments[0]);
            if (!file) {
                throw ExecutionException("wc: cannot open file '" + arguments[0] + "'");
            }
            stringstream buffer;
            buffer << file.rdbuf();
            data = buffer.str();
        }
    }
    // If no arguments, read from standard input
    else {
        data = readInput();
    }

    // Counts characters if -c option is used
    if (option == "-c") {
        writeOutput(to_string(data.size()));
    }
    // Default: count words
    else {
        size_t count = 0;
        istringstream iss(data);
        string word;
        while (iss >> word) {
            count++;
        }
        writeOutput(to_string(count));
    }
}

// Validates that a correct option is provided
void Wc::validate() {
    if (option.empty()) {
        throw SemanticException("wc: option is required. Use -w or -c");
    }
    if (option != "-w" && option != "-c") {
        throw SemanticException("wc: invalid option '" + option + "'. Use -w or -c");
    }
}