#include "Head.h"
#include "Exceptions.h"

#include <iostream>
#include <fstream>
#include <sstream>

// Constructor
Head::Head() : count(0) {}
// Destructor
Head::~Head() {}

// Validates and parses the required -n<count> option
void Head::validate() {
    if (option.empty()) {
        throw SemanticException("head: option -n<count> is required");
    }

    // Option starts with -n
    if (option.rfind("-n", 0) != 0) {
        throw SyntaxException("head: invalid option '" + option + "'. Required format: -n<count>");
    }

    // Get the number part of the option
    string num_part = option.substr(2);
    if (num_part.empty()) {
        throw SyntaxException("head: option -n requires a number");
    }

    // Convert the number part to int
    try {
        count = stoi(num_part);
    }
    catch (const std::exception&) {
        throw SyntaxException("head: invalid number format after -n");
    }

    // Line count not negative
    if (count < 0) {
        throw SemanticException("head: invalid line count '" + num_part + "'");
    }
}

// Prints the first 'n' lines from a file or piped input
void Head::execute() {
    string data;
    // Read from a file if an argument given
    if (!arguments.empty()) {
        ifstream file(arguments[0]);
        if (!file.is_open()) {
            throw ExecutionException("head: cannot open '" + arguments[0] + "' for reading");
        }
        stringstream buffer;
        buffer << file.rdbuf();
        data = buffer.str();
    }
    // Else, from standard input
    else {
        data = readInput();
    }

    // Print the specified number of lines to the output
    istringstream iss(data);
    string line;
    for (int i = 0; i < count && getline(iss, line); ++i) {
        writeOutput(line + "\n");
    }
}