#include "Rm.h"
#include "Exceptions.h"
#include <cstdio> 

// Constructor
Rm::Rm() {}
// Destructor
Rm::~Rm() {}

// Attempts to delete the file (argument)
void Rm::execute() {
    if (std::remove(arguments[0].c_str()) != 0) {
        throw ExecutionException("rm: cannot remove '" + arguments[0] + "': No such file or directory or permission issue");
    }
}

// Rm command has exactly one argument and no options
void Rm::validate() {
    if (arguments.size() != 1) {
        throw SemanticException("rm: missing file operand");
    }
    if (!option.empty()) {
        throw SemanticException("rm: does not take any options");
    }
}