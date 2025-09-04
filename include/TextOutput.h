// TextOutput.h
#ifndef _textoutput_h_
#define _textoutput_h_

#include "OutputSink.h"
#include <string>
using namespace std;

// Output to a string
class TextOutput : public OutputSink {
    // Reference to string buffer
    string& buffer;
public:
    // Constructor
    explicit TextOutput(string& buf) : buffer(buf) {}

    // Append data to buffer
    void sendOutput(const string& data) override {
        buffer.append(data);
    }
};

#endif