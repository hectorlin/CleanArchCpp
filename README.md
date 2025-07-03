# CleanArchCpp - Clean Architecture & C++11 Examples

A comprehensive C++ project demonstrating Clean Architecture principles and complete C++11 keyword examples with bilingual documentation.

## 🏗️ Project Overview

This repository showcases:
- **Clean Architecture Implementation** in C++
- **Complete C++11 Keywords** with practical examples
- **Operating System Detection** utilities
- **Modern C++ Best Practices**

## 📁 Project Structure

```
CleanArchCpp/
├── clean_architecture_example.cpp    # Clean Architecture demonstration
├── clean_architecture_example        # Compiled executable
├── os_detector.cpp                   # OS detection utility
├── os_detector                       # Compiled executable
├── kw_*.cpp                          # C++11 keyword examples (72 files)
├── kw_*                              # Compiled keyword examples
├── Makefile                          # Build configuration
├── .gitignore                        # Git ignore rules
└── README.md                         # This documentation
```

## 🎯 Main Features

### 1. Clean Architecture Example
- **Domain Layer**: Business logic and entities
- **Use Case Layer**: Application-specific business rules
- **Interface Adapter Layer**: Controllers and presenters
- **Framework Layer**: External interfaces and tools

### 2. C++11 Keywords Complete Coverage
- **72 Individual Examples** covering all C++11 keywords
- **Bilingual Comments** (English/Chinese)
- **Fully Compilable** and runnable code
- **Practical Use Cases** for each keyword

### 3. Operating System Detection
- **Cross-platform** OS detection utility
- **Runtime** platform identification
- **Compile-time** feature detection

## 🚀 Quick Start

### Prerequisites
- C++11 compatible compiler (GCC 4.8+, Clang 3.3+, MSVC 2015+)
- Make (optional, for using Makefile)

### Building the Project

```bash
# Build all components
make

# Build specific components
make clean_architecture_example
make os_detector
make keywords

# Clean build artifacts
make clean
```

### Running Examples

```bash
# Run Clean Architecture example
./clean_architecture_example

# Run OS detector
./os_detector

# Run all keyword examples
for file in kw_*.cpp; do
    echo "=== Running ${file%.cpp} ==="
    "./${file%.cpp}"
    echo
done
```

## 📚 C++11 Keywords Covered

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

## 🏛️ Clean Architecture Principles

The project demonstrates Clean Architecture with:

1. **Independence of Frameworks**: Core business logic is independent of external frameworks
2. **Testability**: Business rules can be tested without UI, database, or external elements
3. **Independence of UI**: UI can change easily without changing the rest of the system
4. **Independence of Database**: Business rules are not bound to the database
5. **Independence of any external agency**: Business rules don't know anything about the outside world

## 🔧 Development

### Compiling Individual Files

```bash
# Clean Architecture example
g++ -std=c++11 -o clean_architecture_example clean_architecture_example.cpp

# OS detector
g++ -std=c++11 -o os_detector os_detector.cpp

# Keyword examples
g++ -std=c++11 -o kw_auto kw_auto.cpp
```

### Code Style
- Follow C++11 standards
- Use meaningful variable names
- Include bilingual comments
- Maintain clean, readable code structure

## 📖 Documentation

Each keyword example includes:
- **English comments** explaining the concept
- **Chinese comments** for bilingual support
- **Practical usage** examples
- **Compilation instructions**

## 🤝 Contributing

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Add appropriate tests
5. Submit a pull request

## 📄 License

This project is open source and available under the MIT License.

## 👨‍💻 Author

**silverlin2@msn.com**

## 🌟 Features Summary

- ✅ **Clean Architecture** implementation
- ✅ **72 C++11 keywords** with examples
- ✅ **Cross-platform** compatibility
- ✅ **Bilingual documentation** (English/Chinese)
- ✅ **Fully compilable** and runnable
- ✅ **OS detection** utilities
- ✅ **Modern C++** best practices
- ✅ **Comprehensive** documentation

---

**Happy Coding! 🚀** 