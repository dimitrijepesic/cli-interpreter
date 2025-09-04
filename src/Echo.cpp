#include "Echo.h"
#include "TextInput.h"
#include "FileInput.h"
#include "Exceptions.h"

#include <memory>
#include <string>

using namespace std;

// Constructor 
Echo::Echo() {}
// Destructor 
Echo::~Echo() {}

// Writes arguments or piped input to the output
void Echo::execute() {
    // If there is an argument - input stream
    if (!arguments.empty()) {
        // Quoted argument - text
        if (firstArgumentQuoted) {
            setInputStream(make_shared<TextInput>(arguments[0]));
        }
		// Else, file input
        else {
            setInputStream(make_shared<FileInput>(arguments[0]));
        }
    }
	// Read from input stream and write to output
    string data = readInput();
    writeOutput(data);
}

// Echo is called with max one argument and no options
void Echo::validate() {
    if (arguments.size() > 1) {
        throw SemanticException("echo: takes at most one argument");
    }
    if (!option.empty()) {
        throw SemanticException("echo: does not take any options");
    }
}