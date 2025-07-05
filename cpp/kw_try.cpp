// try 示例 / Example
#include <iostream>
#include <stdexcept>
int main() {
    try {
        throw std::runtime_error("Test exception / 测试异常");
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
    return 0;
} 