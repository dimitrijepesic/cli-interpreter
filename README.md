# CLI Interpreter

A simple command-line interpreter written in C++, featuring a modular OOP design with support for built-in commands, file redirection, and piping.

## ✨ Features
- **Built-in commands:**
  - `echo`, `date`, `time`, `head -nX`, `wc -w/-c`
  - `touch`, `rm`, `truncate`, `tr`
  - `prompt "newPr"`, `batch file`
- **Stream abstraction:** unified interface for file input/output, console output, pipes, and text streams.
- **Error handling:** custom exception hierarchy (lexical, syntax, semantic, execution).
- **Batch mode:** execute commands from a script file.
- **Extensible:** easy to add new commands by extending the `Command` class.

## 🚀 Build
Requirements:
- CMake ≥ 3.16
- C++17 compiler (GCC, Clang, or MSVC)

```bash
cmake -S . -B build
cmake --build build
./build/cli-shell
