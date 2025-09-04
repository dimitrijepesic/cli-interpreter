#include "Touch.h"
#include "Exceptions.h"
#include <fstream>

// Constructor
Touch::Touch() {}
// Destructor
Touch::~Touch() {}

// Creates a new file if it does not already exist
void Touch::execute() {
    std::ifstream testFile(arguments[0]);
    if (testFile.good()) {
        testFile.close();
        throw ExecutionException("touch: cannot create file '" + arguments[0] + "': File exists");
    }

    std::ofstream file(arguments[0]);
    if (!file.is_open()) {
        throw ExecutionException("touch: cannot create file '" + arguments[0] + "': Permission denied or invalid path");
    }
    file.close();
}

// Touch command has exactly one argument and no options
void Touch::validate() {
    if (arguments.size() != 1) {
        throw SemanticException("touch: missing file operand");
    }
    if (!option.empty()) {
        throw SemanticException("touch: does not take any options");
    }
}