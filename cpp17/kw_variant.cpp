#include <iostream>
#include <string>
#include <variant>
#include <vector>

// C++17: std::variant - 类型安全的联合体
// C++17: std::variant - type-safe unions

// C++17 之前，需要使用 union 或 void* 来处理多种类型
// Before C++17, you had to use union or void* to handle multiple types
// C++17 的 std::variant 提供了类型安全的解决方案
// C++17 std::variant provides a type-safe solution

// 基本用法
// Basic usage
using Number = std::variant<int, double, std::string>;

// 访问 variant 的函数
// Function to access variant
void print_number(const Number& num) {
    std::visit([](const auto& value) {
        std::cout << "Value: " << value << " (type: " << typeid(value).name() << ")" << std::endl;
    }, num);
}

// 使用 std::holds_alternative 检查类型
// Using std::holds_alternative to check type
void check_number_type(const Number& num) {
    if (std::holds_alternative<int>(num)) {
        std::cout << "It's an int: " << std::get<int>(num) << std::endl;
    } else if (std::holds_alternative<double>(num)) {
        std::cout << "It's a double: " << std::get<double>(num) << std::endl;
    } else if (std::holds_alternative<std::string>(num)) {
        std::cout << "It's a string: " << std::get<std::string>(num) << std::endl;
    }
}

// 使用 std::get_if 安全访问
// Using std::get_if for safe access
void safe_access(const Number& num) {
    if (auto int_val = std::get_if<int>(&num)) {
        std::cout << "Int value: " << *int_val << std::endl;
    } else if (auto double_val = std::get_if<double>(&num)) {
        std::cout << "Double value: " << *double_val << std::endl;
    } else if (auto string_val = std::get_if<std::string>(&num)) {
        std::cout << "String value: " << *string_val << std::endl;
    }
}

// 使用 variant 的类
// Class using variant
class Value {
    std::variant<int, double, std::string> data_;
    
public:
    // 构造函数重载
    // Constructor overloads
    Value(int val) : data_(val) {}
    Value(double val) : data_(val) {}
    Value(const std::string& val) : data_(val) {}
    
    // 获取值的方法
    // Methods to get values
    template<typename T>
    T get() const {
        return std::get<T>(data_);
    }
    
    template<typename T>
    bool is() const {
        return std::holds_alternative<T>(data_);
    }
    
    // 转换为字符串
    // Convert to string
    std::string to_string() const {
        return std::visit([](const auto& value) -> std::string {
            if constexpr (std::is_same_v<std::decay_t<decltype(value)>, std::string>) {
                return value;
            } else {
                return std::to_string(value);
            }
        }, data_);
    }
    
    // 打印信息
    // Print information
    void print() const {
        std::visit([](const auto& value) {
            std::cout << "Value: " << value << std::endl;
        }, data_);
    }
};

// 使用 variant 进行错误处理
// Using variant for error handling
using Result = std::variant<int, std::string>;  // int = success, string = error

Result divide(int a, int b) {
    if (b == 0) {
        return std::string("Division by zero");
    }
    return a / b;
}

// 使用 variant 实现状态机
// Using variant to implement state machine
enum class State { Idle, Running, Paused, Stopped };

struct IdleState {};
struct RunningState { int progress; };
struct PausedState { int progress; };
struct StoppedState { std::string reason; };

using StateMachine = std::variant<IdleState, RunningState, PausedState, StoppedState>;

class Process {
    StateMachine state_;
    
public:
    Process() : state_(IdleState{}) {}
    
    void start() {
        if (std::holds_alternative<IdleState>(state_)) {
            state_ = RunningState{0};
            std::cout << "Process started" << std::endl;
        }
    }
    
    void pause() {
        if (auto running = std::get_if<RunningState>(&state_)) {
            state_ = PausedState{running->progress};
            std::cout << "Process paused at " << running->progress << "%" << std::endl;
        }
    }
    
    void resume() {
        if (auto paused = std::get_if<PausedState>(&state_)) {
            state_ = RunningState{paused->progress};
            std::cout << "Process resumed at " << paused->progress << "%" << std::endl;
        }
    }
    
    void stop(const std::string& reason = "User stopped") {
        state_ = StoppedState{reason};
        std::cout << "Process stopped: " << reason << std::endl;
    }
    
    void update() {
        if (auto running = std::get_if<RunningState>(&state_)) {
            running->progress += 10;
            if (running->progress >= 100) {
                state_ = StoppedState{"Completed"};
                std::cout << "Process completed" << std::endl;
            } else {
                std::cout << "Progress: " << running->progress << "%" << std::endl;
            }
        }
    }
    
    void print_state() const {
        std::visit([](const auto& state) {
            using T = std::decay_t<decltype(state)>;
            if constexpr (std::is_same_v<T, IdleState>) {
                std::cout << "State: Idle" << std::endl;
            } else if constexpr (std::is_same_v<T, RunningState>) {
                std::cout << "State: Running (" << state.progress << "%)" << std::endl;
            } else if constexpr (std::is_same_v<T, PausedState>) {
                std::cout << "State: Paused (" << state.progress << "%)" << std::endl;
            } else if constexpr (std::is_same_v<T, StoppedState>) {
                std::cout << "State: Stopped (" << state.reason << ")" << std::endl;
            }
        }, state_);
    }
};

int main() {
    std::cout << "=== C++17 std::variant Demo ===" << std::endl;
    
    // 基本用法
    // Basic usage
    Number num1 = 42;
    Number num2 = 3.14;
    Number num3 = "Hello C++17";
    
    print_number(num1);
    print_number(num2);
    print_number(num3);
    
    // 类型检查
    // Type checking
    check_number_type(num1);
    check_number_type(num2);
    check_number_type(num3);
    
    // 安全访问
    // Safe access
    safe_access(num1);
    safe_access(num2);
    safe_access(num3);
    
    // 使用类
    // Using classes
    Value val1(100);
    Value val2(2.718);
    Value val3("Pi");
    
    val1.print();
    val2.print();
    val3.print();
    
    std::cout << "val1 is int: " << std::boolalpha << val1.is<int>() << std::endl;
    std::cout << "val2 is double: " << std::boolalpha << val2.is<double>() << std::endl;
    std::cout << "val3 is string: " << std::boolalpha << val3.is<std::string>() << std::endl;
    
    // 错误处理
    // Error handling
    auto result1 = divide(10, 2);
    if (auto success = std::get_if<int>(&result1)) {
        std::cout << "Division successful: " << *success << std::endl;
    } else if (auto error = std::get_if<std::string>(&result1)) {
        std::cout << "Division failed: " << *error << std::endl;
    }
    
    auto result2 = divide(10, 0);
    if (auto success = std::get_if<int>(&result2)) {
        std::cout << "Division successful: " << *success << std::endl;
    } else if (auto error = std::get_if<std::string>(&result2)) {
        std::cout << "Division failed: " << *error << std::endl;
    }
    
    // 状态机
    // State machine
    Process process;
    process.print_state();
    
    process.start();
    process.print_state();
    
    process.update();
    process.update();
    process.print_state();
    
    process.pause();
    process.print_state();
    
    process.resume();
    process.print_state();
    
    for (int i = 0; i < 8; ++i) {
        process.update();
    }
    process.print_state();
    
    // 使用 variant 的容器
    // Container using variant
    std::vector<Number> numbers = {42, 3.14, "Hello", 100, 2.718};
    
    std::cout << "Numbers in vector:" << std::endl;
    for (const auto& num : numbers) {
        print_number(num);
    }
    
    return 0;
} 