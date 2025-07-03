// register 示例 / Example (C++11中已弃用，C++17中移除 / Deprecated in C++11, removed in C++17)
#include <iostream>
int main() {
    register int x = 42; // 建议编译器将变量放在寄存器中 / Suggest compiler to put variable in register
    std::cout << "register variable x = " << x << std::endl;
    return 0;
} 