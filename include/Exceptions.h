// Exceptions.h
#ifndef _exceptions_h_
#define _exceptions_h_

#include <stdexcept>
#include <string>

// Base class for all exceptions
class Exceptions : public std::exception {
private:
    std::string message;

public:
    explicit Exceptions(const std::string& msg)
        : message(msg) {
    }

    // Overriding what
    const char* what() const noexcept override {
        return message.c_str();
    }
};

// Error for an unrecognized command
class UnknownCommandException : public Exceptions {
public:
    explicit UnknownCommandException(const std::string& command)
        : Exceptions("Unknown command: " + command) {
    }
};

// Syntax error during parsing
class SyntaxException : public Exceptions {
public:
    explicit SyntaxException(const std::string& message)
        : Exceptions("Syntax error: " + message) {
    }
};

// Semantic error (incorrect arguments)
class SemanticException : public Exceptions {
public:
    explicit SemanticException(const std::string& message)
        : Exceptions("Semantic error: " + message) {
    }
};

// Error during command execution
class ExecutionException : public Exceptions {
public:
    explicit ExecutionException(const std::string& message)
        : Exceptions("Execution error: " + message) {
    }
};

// Lexical error in the input string
class LexicalException : public Exceptions {
public:
    explicit LexicalException(const std::string& message)
        : Exceptions("Lexical error: " + message) {
    }
};

#endif
