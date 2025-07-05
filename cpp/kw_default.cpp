// default 示例 / Example
#include <iostream>
class MyClass {
public:
    MyClass() = default; // 使用默认构造函数 / Use default constructor
    MyClass(const MyClass&) = default; // 使用默认拷贝构造函数 / Use default copy constructor
    MyClass& operator=(const MyClass&) = default; // 使用默认赋值运算符 / Use default assignment operator
    ~MyClass() = default; // 使用默认析构函数 / Use default destructor
};
int main() {
    MyClass obj1;
    MyClass obj2 = obj1; // 使用默认拷贝构造函数 / Uses default copy constructor
    return 0;
} 