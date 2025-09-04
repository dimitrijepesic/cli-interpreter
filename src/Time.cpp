// Time.cpp
#include "Time.h"
#include "Exceptions.h" 

#include <ctime>
#include <sstream>
#include <iomanip>

#ifdef _MSC_VER
#pragma warning(disable : 4996)
#endif

// Constructor
Time::Time() {}
// Destructor
Time::~Time() {}

// Gets the current system time and writes it to the output
void Time::execute() {
    time_t now = time(0);
    tm* ltm = localtime(&now);

    stringstream ss;
    ss << setfill('0') << setw(2) << ltm->tm_hour << ":"
        << setfill('0') << setw(2) << ltm->tm_min << ":"
        << setfill('0') << setw(2) << ltm->tm_sec;

    writeOutput(ss.str());
}

// Time command is called without arguments or options
void Time::validate() {
    if (!arguments.empty()) {
        throw SemanticException("time: does not take any arguments");
    }
    if (!option.empty()) {
        throw SemanticException("time: does not take any options");
    }
}