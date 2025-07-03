// reinterpret_cast 示例 / Example
#include <iostream>
int main() {
    int x = 42;
    int* ptr = &x;
    uintptr_t addr = reinterpret_cast<uintptr_t>(ptr); // 将指针转换为整数 / Convert pointer to integer
    
    std::cout << "Original value: " << x << std::endl;
    std::cout << "Pointer address: " << ptr << std::endl;
    std::cout << "Address as integer: " << addr << std::endl;
    
    int* ptr2 = reinterpret_cast<int*>(addr); // 将整数转换回指针 / Convert integer back to pointer
    std::cout << "Value through reinterpreted pointer: " << *ptr2 << std::endl;
    return 0;
} 