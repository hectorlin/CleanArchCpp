// static_cast 示例 / Example
#include <iostream>
int main() {
    double d = 3.14;
    int i = static_cast<int>(d); // 静态类型转换 / Static type casting
    
    char c = 'A';
    int charAsInt = static_cast<int>(c); // 字符转整数 / Character to integer
    
    std::cout << "double: " << d << std::endl;
    std::cout << "cast to int: " << i << std::endl;
    std::cout << "char: " << c << std::endl;
    std::cout << "char as int: " << charAsInt << std::endl;
    return 0;
} 