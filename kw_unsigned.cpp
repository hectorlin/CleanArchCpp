// unsigned 示例 / Example
#include <iostream>
int main() {
    unsigned int x = 42; // 无符号整型 / Unsigned integer
    unsigned char c = 255; // 无符号字符 / Unsigned character
    unsigned long long big = 18446744073709551615ULL; // 无符号长长整型 / Unsigned long long
    
    std::cout << "unsigned int x = " << x << std::endl;
    std::cout << "unsigned char c = " << static_cast<int>(c) << std::endl;
    std::cout << "unsigned long long big = " << big << std::endl;
    return 0;
} 