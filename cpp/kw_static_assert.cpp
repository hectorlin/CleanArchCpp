// static_assert 示例 / Example
#include <iostream>
static_assert(sizeof(int) == 4, "int must be 4 bytes"); // 编译期断言 / Compile-time assertion
static_assert(sizeof(char) == 1, "char must be 1 byte");
int main() {
    std::cout << "All static assertions passed / 所有静态断言通过" << std::endl;
    std::cout << "int size: " << sizeof(int) << " bytes" << std::endl;
    std::cout << "char size: " << sizeof(char) << " bytes" << std::endl;
    return 0;
} 