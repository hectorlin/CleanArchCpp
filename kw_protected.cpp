// protected 示例 / Example
#include <iostream>
class Base {
protected: // 受保护成员 / Protected members
    int protectedData;
    void protectedFunction() {
        std::cout << "Protected function / 受保护函数" << std::endl;
    }
public:
    Base(int data) : protectedData(data) {}
};
class Derived : public Base {
public:
    Derived(int data) : Base(data) {}
    void accessProtected() {
        protectedData = 100; // 派生类可以访问受保护成员 / Derived class can access protected members
        protectedFunction();
        std::cout << "Protected data: " << protectedData << std::endl;
    }
};
int main() {
    Derived obj(42);
    obj.accessProtected();
    return 0;
} 