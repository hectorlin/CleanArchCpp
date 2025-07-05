# CleanArchCpp - Clean Architecture & C++ Design Patterns

A comprehensive C++ project demonstrating Clean Architecture principles, C++11 keywords, and modern design patterns with bilingual documentation.

## 🏗️ Project Overview

This repository showcases:
- **Clean Architecture Implementation** in C++
- **Complete C++11 Keywords** with practical examples
- **Modern C++ Design Patterns** and principles
- **Operating System Detection** utilities
- **Modern C++ Best Practices** (C++17/20 features)

## 📁 Project Structure

```
CleanArchCpp/
├── cpp/                              # C++ source files directory
│   ├── clean_architecture_example.cpp    # Clean Architecture demonstration
│   ├── os_detector.cpp                   # OS detection utility
│   ├── dp_*.cpp                          # Design pattern examples (16 files)
│   └── kw_*.cpp                          # C++11 keyword examples (72 files)
├── pattern/                          # Design patterns directory
│   ├── design_principles_list.md         # Design principles documentation
│   ├── dp_*.cpp                         # Basic design pattern examples (16 files)
│   └── dp_*_optimized.cpp               # Modern C++ optimized patterns (16 files)
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

### 3. Modern C++ Design Patterns
- **SOLID Principles** implementation
- **Design Patterns** with modern C++17/20 features
- **Optimized Versions** using smart pointers, templates, concepts
- **Type Erasure** and **RAII** patterns
- **Command Pattern** with modern factory approach

### 4. Operating System Detection
- **Cross-platform** OS detection utility
- **Runtime** platform identification
- **Compile-time** feature detection

## 🚀 Quick Start

### Prerequisites
- C++17/20 compatible compiler (GCC 7+, Clang 5+, MSVC 2017+)
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
for file in cpp/kw_*.cpp; do
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

## 🏛️ Design Patterns & Principles

### SOLID Principles
- **SRP (Single Responsibility Principle)**: Each class has one reason to change
- **OCP (Open/Closed Principle)**: Open for extension, closed for modification
- **LSP (Liskov Substitution Principle)**: Subtypes are substitutable for base types
- **ISP (Interface Segregation Principle)**: Clients shouldn't depend on unused interfaces
- **DIP (Dependency Inversion Principle)**: Depend on abstractions, not concretions

### Modern C++ Patterns
- **RAII (Resource Acquisition Is Initialization)**: Automatic resource management
- **Rule of Three/Five/Zero**: Copy/move semantics best practices
- **PIMPL (Pointer to Implementation)**: Interface/implementation separation
- **CRTP (Curiously Recurring Template Pattern)**: Static polymorphism
- **Type Erasure**: Runtime polymorphism without inheritance
- **Command Pattern**: Encapsulate requests as objects
- **Observer Pattern**: Event-driven programming

### Additional Principles
- **DRY (Don't Repeat Yourself)**: Eliminate code duplication
- **KISS (Keep It Simple, Stupid)**: Simplicity over complexity
- **YAGNI (You Aren't Gonna Need It)**: Avoid premature optimization

## 🔧 Development

### Compiling Individual Files

```bash
# Clean Architecture example
g++ -std=c++17 -o clean_architecture_example cpp/clean_architecture_example.cpp

# OS detector
g++ -std=c++17 -o os_detector cpp/os_detector.cpp

# Design pattern examples
g++ -std=c++17 -o dp_srp cpp/dp_srp.cpp
g++ -std=c++17 -o dp_srp_optimized pattern/dp_srp_optimized.cpp

# Keyword examples
g++ -std=c++17 -o kw_auto cpp/kw_auto.cpp
```

### Code Style
- Follow C++17/20 standards
- Use meaningful variable names
- Include bilingual comments
- Maintain clean, readable code structure
- Prefer modern C++ features (smart pointers, auto, etc.)

## 📖 Documentation

Each example includes:
- **English comments** explaining the concept
- **Chinese comments** for bilingual support
- **Practical usage** examples
- **Compilation instructions**
- **Modern C++ optimizations** where applicable

## 🎨 Design Pattern Examples

### Basic vs Optimized Versions
- **Basic versions**: Demonstrate fundamental concepts
- **Optimized versions**: Show modern C++17/20 implementations
- **Performance improvements**: Smart pointers, move semantics, templates
- **Type safety**: Concepts, static assertions, type erasure

### Key Optimizations
- **Memory Management**: `std::unique_ptr`, `std::shared_ptr`
- **Move Semantics**: Efficient resource transfer
- **Templates & Concepts**: Generic programming with constraints
- **Exception Safety**: RAII and strong exception guarantees
- **Modern Containers**: `std::unordered_map`, `std::array`

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
- ✅ **Modern C++ Design Patterns** (C++17/20)
- ✅ **SOLID Principles** implementation
- ✅ **Cross-platform** compatibility
- ✅ **Bilingual documentation** (English/Chinese)
- ✅ **Fully compilable** and runnable
- ✅ **OS detection** utilities
- ✅ **Modern C++** best practices
- ✅ **Comprehensive** documentation
- ✅ **Optimized versions** with modern features

## 📊 File Statistics

- **Total Files**: 122 source files + documentation
- **cpp/**: 89 files (1 architecture + 1 OS detector + 16 patterns + 72 keywords)
- **pattern/**: 33 files (1 doc + 16 basic patterns + 16 optimized patterns)
- **Design Patterns**: 16 patterns with both basic and optimized implementations

---

**Happy Coding! 🚀** 