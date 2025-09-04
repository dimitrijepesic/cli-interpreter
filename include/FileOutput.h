// FileOutput.h
#ifndef _fileoutput_h_
#define _fileoutput_h_

#include "OutputSink.h"
#include <fstream>
#include <string>

using namespace std;

// Output to a file
class FileOutput : public OutputSink {
    // Path to file
    string filename;
    // Append or overwrite
    bool appendMode;

public:
    // FileOutput constructor
    FileOutput(const string& path, bool append = false) : filename(path), appendMode(append) {}

    // Write data to file
    void sendOutput(const string& data) override {
        ofstream ofs;
        if (appendMode) {
            ofs.open(filename, ios::app);
        }
        else {
            ofs.open(filename);
        }
        ofs << data;
    }
};

#endif