// public 示例 / Example
#include <iostream>
class MyClass {
public: // 公有成员 / Public members
    int publicData;
    void publicFunction() {
        std::cout << "Public function / 公有函数" << std::endl;
    }
    MyClass(int data) : publicData(data) {}
};
int main() {
    MyClass obj(42);
    obj.publicData = 100; // 可以直接访问公有成员 / Can directly access public members
    obj.publicFunction();
    std::cout << "Public data: " << obj.publicData << std::endl;
    return 0;
} 