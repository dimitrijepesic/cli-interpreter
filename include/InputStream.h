// InputStream.h
#ifndef _inputstream_h_
#define _inputstream_h_

#include <string>
#include <memory>
using namespace std;

// Base class for all inputs
class InputStream
{
public:
	virtual ~InputStream() = default;
	virtual string getInput() = 0;
};

#endif