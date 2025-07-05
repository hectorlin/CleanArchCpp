// explicit 示例 / Example
#include <iostream>
class MyClass {
    int value;
public:
    explicit MyClass(int v) : value(v) {} // 显式构造函数 / Explicit constructor
    int getValue() const { return value; }
};
void func(MyClass obj) {
    std::cout << "Value: " << obj.getValue() << std::endl;
}
int main() {
    MyClass obj(42);
    // func(42); // 编译错误！不能隐式转换 / Compile error! No implicit conversion
    func(MyClass(42)); // 显式转换 / Explicit conversion
    return 0;
} 