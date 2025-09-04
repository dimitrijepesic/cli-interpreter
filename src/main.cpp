// main.cpp

#include "CLI.h"

int main() {
	// Create CLI instance and start the program
    auto cli = CLI::singleton();
    cli->begin();
    return 0;
}