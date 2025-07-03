// decltype 示例 / Example
#include <iostream>
#include <typeinfo>
int main() {
    int x = 42;
    decltype(x) y = 100; // y 的类型与 x 相同 / y has same type as x
    decltype(x + y) z = 200; // z 的类型是表达式 x + y 的类型 / z has type of expression x + y
    
    std::cout << "x: " << typeid(x).name() << std::endl;
    std::cout << "y: " << typeid(y).name() << std::endl;
    std::cout << "z: " << typeid(z).name() << std::endl;
    return 0;
} 