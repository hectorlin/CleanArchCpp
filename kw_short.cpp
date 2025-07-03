// short 示例 / Example
#include <iostream>
int main() {
    short x = 32767; // 短整型 / Short integer
    unsigned short y = 65535; // 无符号短整型 / Unsigned short integer
    
    std::cout << "short x = " << x << std::endl;
    std::cout << "unsigned short y = " << y << std::endl;
    std::cout << "Size of short: " << sizeof(short) << " bytes" << std::endl;
    return 0;
} 