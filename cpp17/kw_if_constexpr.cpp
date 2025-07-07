#include <iostream>
#include <type_traits>

// C++17: if constexpr - 编译时条件判断
// C++17: if constexpr - compile-time conditional compilation

template<typename T>
auto get_value(T t) {
    if constexpr (std::is_integral_v<T>) {
        // 编译时确定：如果 T 是整数类型，编译这个分支
        // Compile-time determined: if T is integral type, compile this branch
        return t * 2;
    } else if constexpr (std::is_floating_point_v<T>) {
        // 编译时确定：如果 T 是浮点类型，编译这个分支
        // Compile-time determined: if T is floating point type, compile this branch
        return t + 0.5;
    } else {
        // 编译时确定：其他类型，编译这个分支
        // Compile-time determined: other types, compile this branch
        return t;
    }
}

template<typename T>
void print_info(T value) {
    if constexpr (std::is_same_v<T, int>) {
        std::cout << "Integer: " << value << std::endl;
    } else if constexpr (std::is_same_v<T, double>) {
        std::cout << "Double: " << value << std::endl;
    } else if constexpr (std::is_same_v<T, std::string>) {
        std::cout << "String: " << value << std::endl;
    }
}

int main() {
    std::cout << "=== C++17 if constexpr Demo ===" << std::endl;
    
    // 整数类型
    // Integer type
    int int_val = 10;
    auto result1 = get_value(int_val);
    std::cout << "get_value(" << int_val << ") = " << result1 << std::endl;
    print_info(int_val);
    
    // 浮点类型
    // Floating point type
    double double_val = 3.14;
    auto result2 = get_value(double_val);
    std::cout << "get_value(" << double_val << ") = " << result2 << std::endl;
    print_info(double_val);
    
    // 字符串类型
    // String type
    std::string str_val = "Hello C++17";
    auto result3 = get_value(str_val);
    std::cout << "get_value(\"" << str_val << "\") = " << result3 << std::endl;
    print_info(str_val);
    
    return 0;
} 