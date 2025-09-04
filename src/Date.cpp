#ifdef _MSC_VER
#pragma warning(disable : 4996)
#endif

#include "Date.h"
#include "Exceptions.h"

#include <ctime>
#include <sstream>
#include <iomanip>

// Constructor
Date::Date() {}
// Destructor
Date::~Date() {}

// Get current date and print
void Date::execute() {
    time_t now = time(0);
    tm* ltm = localtime(&now);

    stringstream ss;
    ss << setfill('0') << setw(2) << ltm->tm_mday << "."
        << setfill('0') << setw(2) << (ltm->tm_mon + 1) << "."
        << (ltm->tm_year + 1900);

    writeOutput(ss.str());
}

// Date doesn't take any arguments or options
void Date::validate() {
    if (!arguments.empty()) {
        throw SemanticException("date: does not take any arguments");
    }
    if (!option.empty()) {
        throw SemanticException("date: does not take any options");
    }
}