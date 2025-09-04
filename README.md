# CLI Interpreter

A simple command-line interpreter written in C++, featuring a modular OOP design with support for built-in commands, file redirection, and piping.

## ✨ Features
- **Built-in commands:**
  - `echo`, `date`, `time`, `head -nX`, `wc -w/-c`
  - `touch`, `rm`, `truncate`, `tr`
  - `prompt "newPrompt"`, `batch file`
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
```

# Usage Examples

**Print text and pipe into word count** :

echo "hello world" | wc -w

**Save current time to a file** :

time > time.txt

**Display first 5 lines of a file** :

head -n5 file.txt

**Create and truncate files** :

touch notes.txt
truncate notes.txt

# Structure

include/        # Header files
src/            # Implementation (.cpp files)
tests/          # (optional) Unit tests
CMakeLists.txt  # Build configuration
README.md
.gitignore
LICENSE

