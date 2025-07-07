#include <iostream>
#include <array>
#include <vector>

// C++17: auto template parameters - 自动模板参数
// C++17: auto template parameters - non-type template parameters with auto

// C++17 之前，非类型模板参数需要明确指定类型
// Before C++17, non-type template parameters needed explicit type specification
// C++17 允许使用 auto 让编译器自动推导类型
// C++17 allows using auto for automatic type deduction

// 使用 auto 作为非类型模板参数
// Using auto as non-type template parameter
template<auto Value>
struct AutoTemplate {
    static constexpr auto value = Value;
    
    void print() const {
        std::cout << "Value: " << Value << " (type: " << typeid(Value).name() << ")" << std::endl;
    }
};

// 多个 auto 参数
// Multiple auto parameters
template<auto First, auto Second>
struct Pair {
    static constexpr auto first = First;
    static constexpr auto second = Second;
    
    void print() const {
        std::cout << "Pair: (" << First << ", " << Second << ")" << std::endl;
    }
};

// 带类型约束的 auto 参数 (C++20 特性，这里用 SFINAE 替代)
// Auto parameters with type constraints (C++20 feature, using SFINAE here)
template<auto Value, typename = std::enable_if_t<std::is_integral_v<decltype(Value)>>>
struct IntegralTemplate {
    static constexpr auto value = Value;
    
    void print() const {
        std::cout << "Integral value: " << Value << std::endl;
    }
};

// 函数模板中的 auto 参数
// Auto parameters in function templates
template<auto Size>
std::array<int, Size> create_array() {
    std::array<int, Size> arr{};
    for (size_t i = 0; i < Size; ++i) {
        arr[i] = static_cast<int>(i * i);
    }
    return arr;
}

// 类模板中的 auto 成员函数
// Auto member functions in class templates
template<typename T>
class Container {
    T data_;
    
public:
    Container(T data) : data_(data) {}
    
    // C++17: auto 返回类型推导
    // C++17: auto return type deduction
    auto get_data() const {
        return data_;
    }
    
    // 带 auto 参数的成员函数
    // Member function with auto parameter
    template<auto Factor>
    auto multiply() const {
        return data_ * Factor;
    }
};

int main() {
    std::cout << "=== C++17 Auto Template Parameters Demo ===" << std::endl;
    
    // 整数类型的 auto 模板参数
    // Integer auto template parameter
    AutoTemplate<42> int_template;
    int_template.print();
    
    // 字符类型的 auto 模板参数
    // Character auto template parameter
    AutoTemplate<'A'> char_template;
    char_template.print();
    
    // 多个 auto 参数
    // Multiple auto parameters
    Pair<10, 20> pair1;
    pair1.print();
    
    Pair<'X', 100> pair2;
    pair2.print();
    
    // 带类型约束的 auto 参数
    // Auto parameters with type constraints
    IntegralTemplate<100> integral_template;
    integral_template.print();
    
    // 函数模板中的 auto 参数
    // Auto parameters in function templates
    auto arr1 = create_array<5>();
    std::cout << "Array with size 5: ";
    for (int val : arr1) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    auto arr2 = create_array<3>();
    std::cout << "Array with size 3: ";
    for (int val : arr2) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    // 类模板中的 auto 成员函数
    // Auto member functions in class templates
    Container<int> container(42);
    auto data = container.get_data();
    std::cout << "Container data: " << data << std::endl;
    
    auto result1 = container.multiply<2>();
    std::cout << "Container data * 2: " << result1 << std::endl;
    
    auto result2 = container.multiply<3>();
    std::cout << "Container data * 3: " << result2 << std::endl;
    
    return 0;
} 