// TextInput.h
#ifndef _textinput_h_
#define _textinput_h_

#include "InputStream.h"
#include <string>
#include <utility>

using namespace std;

// Input from a string
class TextInput : public InputStream {
    // The input string
    string text;
    // Flag for one-time read
    bool consumed = false;
public:
    // Constructor
    TextInput(string t) : text(move(t)) {}

    // Get string content once
    string getInput() override {
        if (consumed) return "";
        consumed = true;
        return text;
    }
};

#endif