# C++ Design Principles

## 1. SOLID Principles
- **S** - Single Responsibility Principle (SRP)
- **O** - Open/Closed Principle (OCP)
- **L** - Liskov Substitution Principle (LSP)
- **I** - Interface Segregation Principle (ISP)
- **D** - Dependency Inversion Principle (DIP)

## 2. DRY (Don't Repeat Yourself)
- Code reuse and abstraction

## 3. KISS (Keep It Simple, Stupid)
- Simplicity in design

## 4. YAGNI (You Aren't Gonna Need It)
- Avoid over-engineering

## 5. RAII (Resource Acquisition Is Initialization)
- Resource management

## 6. Rule of Three/Five/Zero
- Copy constructor, assignment operator, destructor

## 7. PIMPL (Pointer to Implementation)
- Hide implementation details

## 8. CRTP (Curiously Recurring Template Pattern)
- Static polymorphism

## 9. Type Erasure
- Runtime polymorphism without inheritance

## 10. Expression Templates
- Compile-time optimization

## 11. SFINAE (Substitution Failure Is Not An Error)
- Template metaprogramming

## 12. Tag Dispatch
- Function overloading based on types

## 13. Policy-Based Design
- Template-based composition

## 14. Command Pattern
- Encapsulate requests as objects

## 15. Observer Pattern
- Event handling and notifications

## 16. Factory Pattern
- Object creation

## 17. Singleton Pattern
- Single instance management

## 18. Strategy Pattern
- Algorithm selection

## 19. Adapter Pattern
- Interface adaptation

## 20. Decorator Pattern
- Dynamic behavior extension

## 为什么现代C++设计需要命令工厂？ / Why Need Modern Command Factory in C++ Design?

**中文：**
现代C++中引入"命令工厂（Command Factory）"模式，主要是为了提升代码的可扩展性、可维护性和灵活性。传统的命令模式虽然解耦了请求者和执行者，但在实际项目中，命令的种类可能会不断增加或变化。此时，使用工厂模式来统一创建命令对象，可以带来以下好处：

1. **解耦对象创建**：调用者无需关心具体命令类的构造细节，只需通过工厂获取命令对象，降低了依赖。
2. **易于扩展**：新增命令时，只需在工厂中注册即可，无需修改调用逻辑，符合开闭原则（OCP）。
3. **支持运行时动态注册**：现代C++（如C++17/20）可以用`std::function`、`std::unordered_map`等实现命令的动态注册和查找，支持插件式扩展。
4. **统一管理生命周期**：工厂可以统一管理命令对象的生命周期，结合智能指针避免内存泄漏。
5. **便于测试和Mock**：通过工厂注入不同的命令实现，便于单元测试和模拟。

**英文：**
A modern Command Factory in C++ is valuable because it enhances scalability, maintainability, and flexibility of your codebase. While the classic Command Pattern decouples the invoker from the receiver, real-world projects often require adding or changing command types dynamically. Using a factory to create command objects brings several advantages:

1. **Decouples Object Creation**: The caller doesn't need to know the details of command construction—just asks the factory, reducing dependencies.
2. **Easy to Extend**: Adding new commands only requires registering them with the factory, not changing the invocation logic—adhering to the Open/Closed Principle (OCP).
3. **Supports Runtime Registration**: Modern C++ (C++17/20) allows dynamic registration and lookup of commands using `std::function`, `std::unordered_map`, etc., enabling plugin-like extensibility.
4. **Centralized Lifecycle Management**: The factory can manage the lifecycle of command objects, using smart pointers to prevent memory leaks.
5. **Testability and Mocking**: You can inject different command implementations via the factory, making unit testing and mocking easier.

**总结 / Summary：**
现代C++的命令工厂模式让你的命令体系更灵活、可扩展、易维护，是大型或可插拔系统中推荐的设计方式。
In summary, a modern command factory makes your command system more flexible, extensible, and maintainable—highly recommended for large or pluggable C++ systems. 