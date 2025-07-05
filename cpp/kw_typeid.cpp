// typeid 示例 / Example
#include <iostream>
#include <typeinfo>
int main() {
    int x = 42;
    double y = 3.14;
    std::string str = "Hello";
    
    std::cout << "Type of x: " << typeid(x).name() << std::endl;
    std::cout << "Type of y: " << typeid(y).name() << std::endl;
    std::cout << "Type of str: " << typeid(str).name() << std::endl;
    
    if (typeid(x) == typeid(int)) {
        std::cout << "x is of type int / x 是 int 类型" << std::endl;
    }
    return 0;
} 