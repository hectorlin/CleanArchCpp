// const 示例 / Example
#include <iostream>
int main() {
    const int x = 42; // 常量变量 / Constant variable
    const int* ptr = &x; // 指向常量的指针 / Pointer to constant
    int* const constPtr = nullptr; // 常量指针 / Constant pointer
    const int* const constPtrToConst = &x; // 指向常量的常量指针 / Constant pointer to constant
    
    std::cout << "x = " << x << std::endl;
    return 0;
} 