// private 示例 / Example
#include <iostream>
class MyClass {
private: // 私有成员 / Private members
    int privateData;
    void privateFunction() {
        std::cout << "Private function called / 调用私有函数" << std::endl;
    }
public: // 公有成员 / Public members
    MyClass(int data) : privateData(data) {}
    void publicFunction() {
        privateFunction(); // 公有函数可以调用私有函数 / Public function can call private function
        std::cout << "Private data: " << privateData << std::endl;
    }
};
int main() {
    MyClass obj(42);
    obj.publicFunction();
    // obj.privateFunction(); // 编译错误！不能从外部访问私有成员 / Compile error! Cannot access private member
    return 0;
} 