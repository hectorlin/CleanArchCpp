// void 示例 / Example
#include <iostream>
void printMessage() { // 无返回值的函数 / Function with no return value
    std::cout << "Hello World" << std::endl;
}
void* getAddress(int& value) { // 返回 void 指针 / Return void pointer
    return &value;
}
int main() {
    printMessage();
    
    int x = 42;
    void* ptr = getAddress(x);
    std::cout << "Address of x: " << ptr << std::endl;
    return 0;
} 