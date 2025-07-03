// nullptr 示例 / Example
#include <iostream>
void func(int* ptr) {
    if (ptr == nullptr) {
        std::cout << "Pointer is null / 指针为空" << std::endl;
    } else {
        std::cout << "Pointer is not null / 指针不为空" << std::endl;
    }
}
int main() {
    int* ptr1 = nullptr; // C++11 空指针 / C++11 null pointer
    int* ptr2 = NULL; // 传统方式 / Traditional way
    func(ptr1);
    func(ptr2);
    return 0;
} 