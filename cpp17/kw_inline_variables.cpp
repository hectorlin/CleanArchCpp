#include <iostream>
#include <string>

// C++17: inline variables - 内联变量
// C++17: inline variables - allows multiple definitions in header files

// 在 C++17 之前，需要在头文件中声明，在源文件中定义
// Before C++17, you had to declare in header and define in source file
// 现在可以直接在头文件中定义内联变量
// Now you can define inline variables directly in header files

// 内联常量
// Inline constants
inline const int MAX_SIZE = 100;
inline const std::string DEFAULT_NAME = "Unknown";

// 内联静态变量
// Inline static variables
inline static int global_counter = 0;

// 内联函数中的静态变量
// Static variables in inline functions
inline int get_next_id() {
    static int id = 0;
    return ++id;
}

// 模板内联变量
// Template inline variables
template<typename T>
inline T default_value = T{};

// 特化模板内联变量
// Specialized template inline variables
template<>
inline int default_value<int> = 42;

template<>
inline std::string default_value<std::string> = "Default String";

// 类中的内联静态成员
// Inline static members in classes
class Config {
public:
    inline static const std::string VERSION = "1.0.0";
    inline static int instance_count = 0;
    
    Config() {
        instance_count++;
    }
    
    ~Config() {
        instance_count--;
    }
};

int main() {
    std::cout << "=== C++17 Inline Variables Demo ===" << std::endl;
    
    // 使用内联常量
    // Using inline constants
    std::cout << "MAX_SIZE: " << MAX_SIZE << std::endl;
    std::cout << "DEFAULT_NAME: " << DEFAULT_NAME << std::endl;
    
    // 使用内联静态变量
    // Using inline static variables
    global_counter++;
    std::cout << "Global counter: " << global_counter << std::endl;
    
    // 使用内联函数
    // Using inline functions
    std::cout << "Next ID: " << get_next_id() << std::endl;
    std::cout << "Next ID: " << get_next_id() << std::endl;
    
    // 使用模板内联变量
    // Using template inline variables
    std::cout << "Default int: " << default_value<int> << std::endl;
    std::cout << "Default string: " << default_value<std::string> << std::endl;
    std::cout << "Default double: " << default_value<double> << std::endl;
    
    // 使用类中的内联静态成员
    // Using inline static members in classes
    std::cout << "Config version: " << Config::VERSION << std::endl;
    std::cout << "Initial instance count: " << Config::instance_count << std::endl;
    
    {
        Config config1;
        Config config2;
        std::cout << "After creating 2 instances: " << Config::instance_count << std::endl;
    }
    
    std::cout << "After destroying instances: " << Config::instance_count << std::endl;
    
    return 0;
} 