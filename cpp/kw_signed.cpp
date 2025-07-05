// signed 示例 / Example
#include <iostream>
int main() {
    signed int x = -42; // 有符号整型 / Signed integer
    signed char c = -128; // 有符号字符 / Signed character
    
    std::cout << "signed int x = " << x << std::endl;
    std::cout << "signed char c = " << static_cast<int>(c) << std::endl;
    return 0;
} 