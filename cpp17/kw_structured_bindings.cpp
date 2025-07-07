#include <iostream>
#include <string>
#include <tuple>
#include <array>
#include <map>
#include <vector>

// C++17: Structured Bindings - 结构化绑定
// C++17: Structured Bindings - unpack values from tuples, pairs, arrays, etc.

// C++17 之前，需要手动解包复合类型
// Before C++17, you had to manually unpack composite types
// C++17 的结构化绑定让这变得简单
// C++17 structured bindings make this much simpler

// 简单的结构体
// Simple struct
struct Point {
    int x, y;
    std::string name;
};

// 返回多个值的函数
// Function returning multiple values
std::tuple<int, double, std::string> get_data() {
    return {42, 3.14, "Hello C++17"};
}

// 返回 pair 的函数
// Function returning pair
std::pair<int, std::string> get_status() {
    return {200, "OK"};
}

// 返回数组的函数
// Function returning array
std::array<int, 3> get_coordinates() {
    return {10, 20, 30};
}

// 返回结构体的函数
// Function returning struct
Point get_point() {
    return {100, 200, "Origin"};
}

// 带引用的结构化绑定
// Structured bindings with references
void modify_point(Point& p) {
    auto& [x, y, name] = p;
    x += 10;
    y += 20;
    name += " Modified";
}

// 忽略某些元素的结构化绑定
// Structured bindings ignoring some elements
std::tuple<int, double, std::string, bool> get_complex_data() {
    return {1, 2.5, "test", true};
}

// 在循环中使用结构化绑定
// Using structured bindings in loops
void process_map() {
    std::map<std::string, int> scores = {
        {"Alice", 95},
        {"Bob", 87},
        {"Charlie", 92}
    };
    
    std::cout << "Scores:" << std::endl;
    for (const auto& [name, score] : scores) {
        std::cout << name << ": " << score << std::endl;
    }
}

// 在 lambda 中使用结构化绑定
// Using structured bindings in lambdas
auto create_processor() {
    return [](const auto& pair) {
        auto [first, second] = pair;
        std::cout << "Processing: " << first << " -> " << second << std::endl;
    };
}

// 嵌套的结构化绑定
// Nested structured bindings
void nested_bindings() {
    std::vector<std::pair<std::string, std::pair<int, double>>> data = {
        {"A", {1, 1.1}},
        {"B", {2, 2.2}},
        {"C", {3, 3.3}}
    };
    
    for (const auto& item : data) {
        auto [key, inner_pair] = item;
        auto [num, val] = inner_pair;
        std::cout << key << ": (" << num << ", " << val << ")" << std::endl;
    }
}

int main() {
    std::cout << "=== C++17 Structured Bindings Demo ===" << std::endl;
    
    // 解包 tuple
    // Unpacking tuple
    auto [number, pi, message] = get_data();
    std::cout << "Tuple unpacked: " << number << ", " << pi << ", " << message << std::endl;
    
    // 解包 pair
    // Unpacking pair
    auto [code, status] = get_status();
    std::cout << "Pair unpacked: " << code << ", " << status << std::endl;
    
    // 解包数组
    // Unpacking array
    auto [x, y, z] = get_coordinates();
    std::cout << "Array unpacked: " << x << ", " << y << ", " << z << std::endl;
    
    // 解包结构体
    // Unpacking struct
    auto [px, py, pname] = get_point();
    std::cout << "Struct unpacked: " << px << ", " << py << ", " << pname << std::endl;
    
    // 带引用的结构化绑定
    // Structured bindings with references
    Point point = {50, 60, "Test"};
    std::cout << "Before modification: " << point.x << ", " << point.y << ", " << point.name << std::endl;
    modify_point(point);
    std::cout << "After modification: " << point.x << ", " << point.y << ", " << point.name << std::endl;
    
    // 忽略某些元素
    // Ignoring some elements
    auto [num, val, str, _] = get_complex_data();
    std::cout << "Complex data (ignoring bool): " << num << ", " << val << ", " << str << std::endl;
    
    // 在循环中使用
    // Using in loops
    process_map();
    
    // 在 lambda 中使用
    // Using in lambdas
    auto processor = create_processor();
    processor(std::make_pair("Key", "Value"));
    
    // 嵌套绑定
    // Nested bindings
    nested_bindings();
    
    // 直接解包字面量
    // Direct unpacking of literals
    auto [a, b, c] = std::array{1, 2, 3};
    std::cout << "Literal array: " << a << ", " << b << ", " << c << std::endl;
    
    auto [first, second] = std::pair{"Hello", "World"};
    std::cout << "Literal pair: " << first << ", " << second << std::endl;
    
    return 0;
} 