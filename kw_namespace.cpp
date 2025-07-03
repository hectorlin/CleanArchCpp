// namespace 示例 / Example
#include <iostream>
namespace MyNamespace {
    int x = 42;
    void func() {
        std::cout << "Function in namespace / 命名空间中的函数" << std::endl;
    }
}
namespace AnotherNamespace {
    int x = 100;
}
int main() {
    std::cout << "MyNamespace::x = " << MyNamespace::x << std::endl;
    std::cout << "AnotherNamespace::x = " << AnotherNamespace::x << std::endl;
    MyNamespace::func();
    return 0;
} 