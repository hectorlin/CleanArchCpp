// delete 示例 / Example
#include <iostream>
class MyClass {
public:
    MyClass() = default;
    MyClass(const MyClass&) = delete; // 禁用拷贝构造函数 / Disable copy constructor
    MyClass& operator=(const MyClass&) = delete; // 禁用赋值运算符 / Disable assignment operator
};
int main() {
    MyClass obj1;
    // MyClass obj2 = obj1; // 编译错误！拷贝构造函数被删除 / Compile error! Copy constructor deleted
    // obj1 = obj2; // 编译错误！赋值运算符被删除 / Compile error! Assignment operator deleted
    return 0;
} 