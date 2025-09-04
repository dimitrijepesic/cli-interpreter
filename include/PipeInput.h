// PipeInput.h
#ifndef _pipeinput_h_
#define _pipeinput_h_

#include "InputStream.h"
#include <iostream>
#include <sstream>
using namespace std;

// Input from standard input
class PipeInput : public InputStream {
public:
	// Constructor
	PipeInput() = default;
	// Read from cin
	string getInput() override {
		ostringstream oss;
		oss << cin.rdbuf();
		return oss.str();
	}
};

#endif