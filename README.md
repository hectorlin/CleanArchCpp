# CleanArchCpp 🏗️

A comprehensive C++ project demonstrating **Clean Architecture principles**, **modern C++17 features**, and **design patterns** with both basic and optimized implementations.

## 📋 Table of Contents

- [Overview](#overview)
- [Project Structure](#project-structure)
- [Features](#features)
- [Design Principles](#design-principles)
- [Design Patterns](#design-patterns)
- [C++ Keywords](#c-keywords)
- [Compilation](#compilation)
- [Usage](#usage)
- [Examples](#examples)
- [Contributing](#contributing)
- [License](#license)

## 🎯 Overview

CleanArchCpp is a learning resource that showcases:
- **Clean Architecture** implementation in C++
- **SOLID principles** with practical examples
- **Modern C++17/20** features and best practices
- **Design patterns** with both basic and optimized versions
- **C++11/14/17 keywords** with usage examples
- **RAII** and resource management patterns

## 📁 Project Structure

```
CleanArchCpp/
├── cpp/                          # Source files
│   ├── clean_architecture_example.cpp
│   ├── os_detector.cpp
│   ├── dp_*.cpp                  # Design pattern examples
│   └── kw_*.cpp                  # C++ keyword examples
├── pattern/                      # Design pattern implementations
│   ├── dp_*.cpp                  # Basic implementations
│   └── dp_*_optimized.cpp        # Modern C++17/20 optimized versions
├── bin/                          # Compiled executables
├── compile_all.sh               # Automated compilation script
├── Makefile                     # Build configuration
└── README.md                    # This file
```

## ✨ Features

### 🏛️ Clean Architecture
- **Domain Layer**: Business logic and entities
- **Application Layer**: Use cases and application services
- **Infrastructure Layer**: External interfaces and implementations
- **Interface Layer**: User interface and controllers

### 🎨 Design Principles
- **SOLID Principles**: Single Responsibility, Open/Closed, Liskov Substitution, Interface Segregation, Dependency Inversion
- **DRY**: Don't Repeat Yourself
- **KISS**: Keep It Simple, Stupid
- **YAGNI**: You Aren't Gonna Need It
- **RAII**: Resource Acquisition Is Initialization

### 🔧 Design Patterns
- **Command Pattern**: Encapsulate requests as objects
- **Observer Pattern**: Define one-to-many dependency
- **CRTP**: Curiously Recurring Template Pattern
- **PIMPL**: Pointer to Implementation
- **Type Erasure**: Hide type information
- **Rule of Three/Five/Zero**: Resource management rules

### 🚀 Modern C++ Features
- **Smart Pointers**: `std::unique_ptr`, `std::shared_ptr`
- **Move Semantics**: Efficient resource transfer
- **Lambda Expressions**: Functional programming
- **Type Deduction**: `auto`, `decltype`
- **Variadic Templates**: Flexible template programming
- **constexpr**: Compile-time evaluation
- **std::optional**: Optional values
- **std::variant**: Type-safe unions

## 🎯 Design Principles

### SOLID Principles

#### 1. Single Responsibility Principle (SRP)
```cpp
// Bad: Class with multiple responsibilities
class UserManager {
    void addUser();
    void sendEmail();
    void saveToDatabase();
    void validateInput();
};

// Good: Single responsibility classes
class UserManager { void addUser(); };
class EmailService { void sendEmail(); };
class DatabaseService { void save(); };
class Validator { void validate(); };
```

#### 2. Open/Closed Principle (OCP)
```cpp
// Open for extension, closed for modification
class Shape {
public:
    virtual double calculateArea() const = 0;
    virtual ~Shape() = default;
};

class Rectangle : public Shape { /* ... */ };
class Circle : public Shape { /* ... */ };
// New shapes can be added without modifying existing code
```

#### 3. Liskov Substitution Principle (LSP)
```cpp
// Derived classes must be substitutable for base classes
class Bird {
public:
    virtual void fly() = 0;
};

class Sparrow : public Bird { /* can fly */ };
class Penguin : public Bird { /* cannot fly - violates LSP */ };
```

#### 4. Interface Segregation Principle (ISP)
```cpp
// Clients shouldn't depend on interfaces they don't use
class Printer {
public:
    virtual void print() = 0;
    virtual void scan() = 0;  // Not all printers can scan
};

// Better: Separate interfaces
class IPrinter { virtual void print() = 0; };
class IScanner { virtual void scan() = 0; };
```

#### 5. Dependency Inversion Principle (DIP)
```cpp
// Depend on abstractions, not concretions
class DatabaseService {
public:
    virtual void save(const std::string& data) = 0;
};

class MySQLService : public DatabaseService { /* ... */ };
class PostgreSQLService : public DatabaseService { /* ... */ };
```

## 🎨 Design Patterns

### Command Pattern
```cpp
class Command {
public:
    virtual void execute() = 0;
    virtual ~Command() = default;
};

class LightOnCommand : public Command {
public:
    void execute() override { light_.turnOn(); }
private:
    Light& light_;
};
```

### Observer Pattern
```cpp
class Observer {
public:
    virtual void update(const std::string& message) = 0;
    virtual ~Observer() = default;
};

class Subject {
public:
    void attach(std::shared_ptr<Observer> observer);
    void notify(const std::string& message);
private:
    std::vector<std::shared_ptr<Observer>> observers_;
};
```

### CRTP (Curiously Recurring Template Pattern)
```cpp
template<typename Derived>
class Base {
public:
    void interface() {
        static_cast<Derived*>(this)->implementation();
    }
};

class Derived : public Base<Derived> {
public:
    void implementation() { /* ... */ }
};
```

## 🔤 C++ Keywords

The project includes examples for all major C++ keywords:

### Basic Keywords
- `auto`, `decltype`, `constexpr`, `noexcept`
- `nullptr`, `override`, `final`, `explicit`
- `virtual`, `static`, `const`, `mutable`

### Modern C++ Keywords
- `alignas`, `alignof`, `thread_local`
- `using`, `typename`, `template`
- `static_assert`, `typeid`, `sizeof`

### Type Keywords
- `bool`, `char`, `int`, `float`, `double`
- `void`, `wchar_t`, `char16_t`, `char32_t`
- `short`, `long`, `signed`, `unsigned`

## 🛠️ Compilation

### Prerequisites
- **Compiler**: GCC 7+ or Clang 5+ with C++17 support
- **OS**: Linux, macOS, or Windows with WSL

### Quick Start
```bash
# Clone the repository
git clone https://github.com/hectorlin/CleanArchCpp.git
cd CleanArchCpp

# Compile all files
./compile_all.sh

# Or use Makefile
make all
```

### Compilation Script
The `compile_all.sh` script provides:
- ✅ **Colored output** for success/failure
- ✅ **Error handling** and reporting
- ✅ **Organized compilation** by directory
- ✅ **Executable management** in `bin/` directory
- ✅ **Progress tracking** with file counts

### Compilation Status
- **Total Files**: 130 C++ source files
- **Success Rate**: 100% (132/132 files compiled)
- **C++ Standard**: C++17 with modern features
- **Warnings**: Minimal, clean code

## 🚀 Usage

### Running Examples
```bash
# Run all executables
cd bin && for file in *; do 
    echo "=== Running $file ==="; 
    ./$file; 
    echo; 
done

# Run specific examples
./bin/dp_srp                    # Single Responsibility Principle
./bin/dp_ocp_optimized          # Open/Closed Principle (optimized)
./bin/kw_auto                   # auto keyword example
./bin/clean_architecture_example # Clean Architecture demo
```

### Learning Path
1. **Start with**: `cpp/kw_*.cpp` - C++ keywords and basics
2. **Continue with**: `cpp/dp_*.cpp` - Basic design patterns
3. **Advanced**: `pattern/dp_*_optimized.cpp` - Modern C++ implementations
4. **Architecture**: `cpp/clean_architecture_example.cpp` - Clean Architecture

## 📚 Examples

### Clean Architecture Example
```cpp
// Domain Layer
class User {
public:
    User(std::string name) : name_(std::move(name)) {}
    const std::string& getName() const { return name_; }
private:
    std::string name_;
};

// Application Layer
class UserService {
public:
    explicit UserService(std::unique_ptr<IUserRepository> repo) 
        : repo_(std::move(repo)) {}
    
    void createUser(const std::string& name) {
        auto user = std::make_unique<User>(name);
        repo_->save(std::move(user));
    }
private:
    std::unique_ptr<IUserRepository> repo_;
};
```

### Modern C++ Features
```cpp
// Smart pointers and move semantics
auto user = std::make_unique<User>("John");
auto service = std::make_unique<UserService>(std::move(repo));

// Lambda expressions
std::for_each(users.begin(), users.end(), 
    [](const auto& user) { user.print(); });

// Type deduction
auto result = calculateArea(5.0, 3.0);  // auto deduction
decltype(result) another_result = 0.0;  // decltype usage
```

## 🤝 Contributing

We welcome contributions! Please:

1. **Fork** the repository
2. **Create** a feature branch
3. **Add** your improvements
4. **Test** compilation with `./compile_all.sh`
5. **Submit** a pull request

### Contribution Guidelines
- Follow **C++17** standard
- Use **modern C++** features where appropriate
- Maintain **clean code** principles
- Add **comprehensive comments**
- Ensure **100% compilation** success

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🙏 Acknowledgments

- **Robert C. Martin** for Clean Architecture principles
- **Gang of Four** for design patterns
- **Bjarne Stroustrup** for C++ language
- **C++ Community** for modern C++ best practices

---

**Happy Coding! 🎉**

*This project demonstrates the power of modern C++ combined with solid software engineering principles.* 