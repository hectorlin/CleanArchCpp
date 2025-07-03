# C++11 Keywords Complete Examples

Complete examples for all C++11 keywords with bilingual comments (English/Chinese).

## Overview

This repository contains 72 individual C++ source files, each demonstrating the usage of a specific C++11 keyword. All examples are fully compilable and runnable.

## Keywords Covered

### Basic Keywords
- `auto`, `bool`, `break`, `case`, `catch`, `char`, `class`, `const`, `continue`
- `default`, `delete`, `do`, `double`, `else`, `enum`, `explicit`, `export`
- `extern`, `false`, `float`, `for`, `friend`, `goto`, `if`, `inline`
- `int`, `long`, `mutable`, `namespace`, `new`, `noexcept`, `nullptr`

### Advanced Keywords
- `operator`, `private`, `protected`, `public`, `register`, `return`
- `short`, `signed`, `sizeof`, `static`, `static_assert`, `struct`
- `switch`, `template`, `this`, `thread_local`, `throw`, `true`
- `try`, `typedef`, `typeid`, `typename`, `union`, `unsigned`
- `using`, `virtual`, `void`, `volatile`, `wchar_t`, `while`

### C++11 New Features
- `alignas`, `alignof`, `char16_t`, `char32_t`, `constexpr`, `decltype`
- `noexcept`, `nullptr`, `static_assert`, `thread_local`

## Compilation

All files can be compiled with C++11 standard:

```bash
# Compile individual file
g++ -std=c++11 -o kw_auto kw_auto.cpp

# Compile all files
for file in kw_*.cpp; do
    g++ -std=c++11 -o "${file%.cpp}" "$file"
done
```

## Running Examples

```bash
# Run individual example
./kw_auto

# Run all examples
for file in kw_*.cpp; do
    echo "=== Running ${file%.cpp} ==="
    "./${file%.cpp}"
    echo
done
```

## Project Structure

```
CleanArchCpp/
├── kw_*.cpp          # Individual keyword examples (72 files)
├── clean_architecture_example.cpp  # Clean Architecture example
├── os_detector.cpp   # OS detection example
├── Makefile          # Build configuration
├── .gitignore        # Git ignore rules
└── README.md         # This file
```

## Features

- ✅ All 72 C++11 keywords covered
- ✅ Bilingual comments (English/Chinese)
- ✅ Fully compilable and runnable
- ✅ Practical examples
- ✅ Cross-platform compatibility
- ✅ Clean Architecture example included

## Requirements

- C++11 compatible compiler (GCC 4.8+, Clang 3.3+, MSVC 2015+)
- Standard C++ library

## License

This project is open source and available under the MIT License.

## Author

silverlin2@msn.com 