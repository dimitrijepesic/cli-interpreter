// CLI.cpp
#include "CLI.h"
#include "TextInput.h"
#include "FileInput.h"
#include "ConsoleOutput.h"
#include "FileOutput.h"
#include "TextOutput.h"
#include <iostream>

using namespace std;

// Define singleton instance
shared_ptr<CLI> CLI::instance = nullptr;

// Constructor
CLI::CLI() : prompt("$"), running(false), parser() {}

// Destructor
CLI::~CLI() {}

// Get or create singleton
shared_ptr<CLI> CLI::singleton() {
    if (!instance) {
        instance = make_shared<CLI>();
    }
    return instance;
}

// Start main loop
void CLI::begin() {
    running = true;
    loop();
}

// Read and execute commands
void CLI::loop() {
    string line;
    while (running) {
        cout << prompt << " " << flush;
        if (!getline(cin, line)) {
            cout << endl;
            break; // Exit on EOF (Ctrl+Z)
        }
        if (line.empty()) {
            continue;
        }
        try {
            execute(line);
        }
        catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
        }
    }
}

// Parse and run one line
void CLI::execute(const string& commLine) {
    auto parsedLine = parser.parse(commLine);
    string pipelineBuffer;

    for (size_t i = 0; i < parsedLine.commands.size(); ++i) {
        const auto& info = parsedLine.commands[i];
        auto cmd = parser.createCommand(info);

        // Configure input
        if (i > 0) {
            cmd->setInputStream(make_shared<TextInput>(pipelineBuffer));
        }
        else if (info.inputRedirection.type == RedirectionInfo::INPUT) {
            cmd->setInputStream(make_shared<FileInput>(info.inputRedirection.filename));
        }

        // Configure output
        bool isLastCommand = (i == parsedLine.commands.size() - 1);
        if (isLastCommand) {
            if (info.outputRedirection.type == RedirectionInfo::OUTPUT || info.outputRedirection.type == RedirectionInfo::OUTPUT_APPEND) {
                bool append = (info.outputRedirection.type == RedirectionInfo::OUTPUT_APPEND);
                cmd->setOutputSink(make_shared<FileOutput>(info.outputRedirection.filename, append));
            }
            else {
                cmd->setOutputSink(make_shared<ConsoleOutput>());
            }
        }
        else {
            pipelineBuffer.clear();
            cmd->setOutputSink(make_shared<TextOutput>(pipelineBuffer));
        }

        // Validate the command and call execute function for each
        try {
            cmd->validate();
            cmd->execute();
        }
        catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
            return; // Stop pipeline on error
        }
    }
}

// Prompt getter
string CLI::getPrompt() const {
    return prompt;
}

// Prompt setter
void CLI::setPrompt(const string& newPrompt) {
    prompt = newPrompt;
}