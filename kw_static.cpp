// static 示例 / Example
#include <iostream>
static int globalVar = 42; // 静态全局变量 / Static global variable
class MyClass {
private:
    static int staticMember; // 静态成员变量 / Static member variable
public:
    static void staticFunction() { // 静态成员函数 / Static member function
        std::cout << "Static function called / 调用静态函数" << std::endl;
    }
    void normalFunction() {
        static int localStatic = 0; // 静态局部变量 / Static local variable
        localStatic++;
        std::cout << "localStatic = " << localStatic << std::endl;
    }
};
int MyClass::staticMember = 100; // 静态成员变量定义 / Static member variable definition
int main() {
    MyClass::staticFunction(); // 通过类名调用静态函数 / Call static function through class name
    MyClass obj1, obj2;
    obj1.normalFunction();
    obj2.normalFunction();
    return 0;
} 