#include <iostream>
#include <string>
#include <vector>

// C++17: Fold Expressions - 折叠表达式
// C++17: Fold Expressions - simplify variadic template operations

// C++17 之前，可变参数模板需要递归实现
// Before C++17, variadic templates required recursive implementation
// C++17 的折叠表达式让这变得简单
// C++17 fold expressions make this much simpler

// 左折叠：((((init op pack1) op pack2) op pack3) ... op packN)
// Left fold: ((((init op pack1) op pack2) op pack3) ... op packN)
template<typename... Args>
auto sum_left(Args... args) {
    return (... + args);  // 左折叠
}

// 右折叠：(pack1 op (pack2 op (pack3 op ... (packN op init))))
// Right fold: (pack1 op (pack2 op (pack3 op ... (packN op init))))
template<typename... Args>
auto sum_right(Args... args) {
    return (args + ...);  // 右折叠
}

// 带初始值的左折叠
// Left fold with initial value
template<typename T, typename... Args>
auto sum_with_init(T init, Args... args) {
    return (init + ... + args);
}

// 带初始值的右折叠
// Right fold with initial value
template<typename T, typename... Args>
auto sum_with_init_right(T init, Args... args) {
    return (args + ... + init);
}

// 逻辑运算折叠
// Logical operation folds
template<typename... Args>
bool all_true(Args... args) {
    return (... && args);  // 所有参数都为真
}

template<typename... Args>
bool any_true(Args... args) {
    return (... || args);  // 任一参数为真
}

// 逗号折叠 - 执行多个操作
// Comma fold - execute multiple operations
template<typename... Args>
void print_all(Args... args) {
    (std::cout << ... << args) << std::endl;
}

// 逗号折叠 - 调用多个函数
// Comma fold - call multiple functions
template<typename... Funcs>
auto call_all(Funcs... funcs) {
    return (... , funcs());  // 返回最后一个函数的结果
}

// 位运算折叠
// Bitwise operation folds
template<typename... Args>
auto bitwise_or(Args... args) {
    return (... | args);
}

template<typename... Args>
auto bitwise_and(Args... args) {
    return (... & args);
}

// 比较运算折叠
// Comparison operation folds
template<typename T, typename... Args>
bool all_equal(T first, Args... args) {
    return (... && (first == args));
}

template<typename T, typename... Args>
bool all_less_than(T max, Args... args) {
    return (... && (args < max));
}

// 复杂折叠表达式
// Complex fold expressions
template<typename... Args>
auto average(Args... args) {
    return (args + ...) / sizeof...(args);
}

template<typename... Args>
auto max_value(Args... args) {
    return (std::max({args...}));
}

// 辅助函数
// Helper functions
int get_value() { return 42; }
double get_double() { return 3.14; }
std::string get_string() { return "Hello"; }

int main() {
    std::cout << "=== C++17 Fold Expressions Demo ===" << std::endl;
    
    // 基本折叠表达式
    // Basic fold expressions
    std::cout << "Left fold sum(1,2,3,4,5): " << sum_left(1, 2, 3, 4, 5) << std::endl;
    std::cout << "Right fold sum(1,2,3,4,5): " << sum_right(1, 2, 3, 4, 5) << std::endl;
    
    // 带初始值的折叠
    // Folds with initial values
    std::cout << "Sum with init(10, 1,2,3): " << sum_with_init(10, 1, 2, 3) << std::endl;
    std::cout << "Sum with init right(10, 1,2,3): " << sum_with_init_right(10, 1, 2, 3) << std::endl;
    
    // 逻辑运算折叠
    // Logical operation folds
    std::cout << "All true(1,1,1,1): " << std::boolalpha << all_true(1, 1, 1, 1) << std::endl;
    std::cout << "All true(1,0,1,1): " << std::boolalpha << all_true(1, 0, 1, 1) << std::endl;
    std::cout << "Any true(0,0,1,0): " << std::boolalpha << any_true(0, 0, 1, 0) << std::endl;
    std::cout << "Any true(0,0,0,0): " << std::boolalpha << any_true(0, 0, 0, 0) << std::endl;
    
    // 逗号折叠
    // Comma folds
    std::cout << "Print all: ";
    print_all("Hello", " ", "C++17", " ", "Fold", " ", "Expressions");
    
    // 函数调用折叠
    // Function call folds
    auto result = call_all(get_value, get_double, get_string);
    std::cout << "Call all result: " << result << std::endl;
    
    // 位运算折叠
    // Bitwise operation folds
    std::cout << "Bitwise OR(1,2,4,8): " << bitwise_or(1, 2, 4, 8) << std::endl;
    std::cout << "Bitwise AND(15,7,3): " << bitwise_and(15, 7, 3) << std::endl;
    
    // 比较运算折叠
    // Comparison operation folds
    std::cout << "All equal(5,5,5,5): " << std::boolalpha << all_equal(5, 5, 5, 5) << std::endl;
    std::cout << "All equal(5,5,6,5): " << std::boolalpha << all_equal(5, 5, 6, 5) << std::endl;
    std::cout << "All less than 10(1,5,9,3): " << std::boolalpha << all_less_than(10, 1, 5, 9, 3) << std::endl;
    std::cout << "All less than 10(1,5,15,3): " << std::boolalpha << all_less_than(10, 1, 5, 15, 3) << std::endl;
    
    // 复杂折叠表达式
    // Complex fold expressions
    std::cout << "Average(1,2,3,4,5): " << average(1, 2, 3, 4, 5) << std::endl;
    std::cout << "Average(10.5, 20.5, 30.5): " << average(10.5, 20.5, 30.5) << std::endl;
    
    return 0;
} 