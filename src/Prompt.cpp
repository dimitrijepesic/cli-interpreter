#include "Prompt.h"
#include "CLI.h"        
#include "Exceptions.h"  

// Constructor
Prompt::Prompt() {}
// Destructor
Prompt::~Prompt() {}

// Sets the CLI prompt to the argument
void Prompt::execute() {
    CLI::singleton()->setPrompt(arguments[0]);
}

// Only one, quoted argument is provided
void Prompt::validate() {
    if (arguments.size() != 1) {
        throw SemanticException("prompt: requires exactly one argument");
    }
    if (!firstArgumentQuoted) {
        throw SemanticException("prompt: argument must be enclosed in quotes");
    }
    if (!option.empty()) {
        throw SemanticException("prompt: does not take any options");
    }
}