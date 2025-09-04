// FileInput.h
#ifndef _fileinput_h_
#define _fileinput_h_

#include "InputStream.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace std;

// Input from a file
class FileInput : public InputStream
{
    // Path to the file
    string filename;
public:
    // Constructor
    FileInput(const string& path) : filename(path) {}

    // Read entire file
    string getInput() override {
        ifstream ifs(filename);
        if (!ifs) {
            throw runtime_error("Cannot open file: " + filename);
        }
        ostringstream oss;
        oss << ifs.rdbuf();
        return oss.str();
    }
};

#endif