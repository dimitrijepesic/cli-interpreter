// OutputSink.h
#ifndef _outputsink_h_
#define _outputsink_h_

#include <string>
using namespace std;

// Base class for all outputs
class OutputSink {
public:
    virtual ~OutputSink() = default;
    virtual void sendOutput(const string& data) = 0;
};

#endif