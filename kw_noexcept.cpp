// noexcept 示例 / Example
#include <iostream>
void func1() noexcept { // 不抛异常的函数 / Function that doesn't throw
    std::cout << "This function won't throw / 这个函数不会抛异常" << std::endl;
}
void func2() noexcept(false) { // 可能抛异常的函数 / Function that might throw
    std::cout << "This function might throw / 这个函数可能抛异常" << std::endl;
}
int main() {
    func1();
    func2();
    return 0;
} 