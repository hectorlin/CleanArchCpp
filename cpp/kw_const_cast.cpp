// const_cast 示例 / Example
#include <iostream>
void printValue(const int* ptr) {
    std::cout << "Value: " << *ptr << std::endl;
}
int main() {
    const int x = 42;
    int* ptr = const_cast<int*>(&x); // 移除 const 限定符 / Remove const qualifier
    *ptr = 100; // 危险操作！修改常量 / Dangerous! Modifying const
    printValue(&x);
    return 0;
} 