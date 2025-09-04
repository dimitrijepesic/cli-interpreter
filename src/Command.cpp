// Command.cpp
#include "Command.h"
#include "ConsoleOutput.h"
#include "PipeInput.h"
#include "Exceptions.h"
#include <stdexcept>

using namespace std;

// Command constructor
Command::Command() {
    // Set default output to console
    output = make_shared<ConsoleOutput>();
}

// Command destructor
Command::~Command() {}

// Read data from input
string Command::readInput() {
    // If no input, default to pipe
    if (!input) {
        input = make_shared<PipeInput>();
    }
    return input->getInput();
}

// Write data to output
void Command::writeOutput(const string& data) {
    // Throw error if output is not set
    if (!output) {
        throw ExecutionException("Output sink not set");
    }
    output->sendOutput(data);
}