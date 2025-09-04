#include "Truncate.h"
#include "Exceptions.h"

#include <fstream>

using namespace std;

// Constructor
Truncate::Truncate() {}
// Destructor
Truncate::~Truncate() {}

// Opens a file to erase its contents
void Truncate::execute() {
    ofstream file(arguments[0], ios::trunc);
    if (!file.is_open()) {
        throw ExecutionException("truncate: cannot open '" + arguments[0] + "': No such file or directory");
    }
    file.close();
}

// Truncate command has exactly one argument and no options
void Truncate::validate() {
    if (arguments.size() != 1) {
        throw SemanticException("truncate: missing file operand");
    }
    if (!option.empty()) {
        throw SemanticException("truncate: does not take any options");
    }
}