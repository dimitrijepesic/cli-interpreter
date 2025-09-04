// ConsoleOutput.h
#ifndef _console_output_h_
#define _console_output_h_

#include "OutputSink.h"
#include <iostream>
#include <string>

using namespace std;

// Output to console
class ConsoleOutput : public OutputSink {
public:
    // Print to console
    void sendOutput(const string& data) override {
        cout << data << endl;
    }
};

#endif