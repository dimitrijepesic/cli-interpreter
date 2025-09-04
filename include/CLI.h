// CLI.h
#ifndef _cli_h_
#define _cli_h_

#include "Parser.h"
#include <string>
#include <memory>

using namespace std;

// Manages the command line
class CLI {
public:
    // Get the single instance
    static shared_ptr<CLI> singleton();

    // Start the CLI
    void begin();

    // Main loop
    void loop();

    // Execute one command line
    void execute(const string& commLine);

    // Get or set prompt string
    string getPrompt() const;
    void setPrompt(const string& prompt);

    CLI();
    ~CLI();

private:
    // The prompt string
    string prompt;
    // Is the loop running
    bool running;
    // The command parser
    Parser parser;

    // Singleton instance pointer
    static shared_ptr<CLI> instance;
};

#endif