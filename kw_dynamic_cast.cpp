// dynamic_cast 示例 / Example
#include <iostream>
class Base {
public:
    virtual ~Base() = default;
    virtual void print() { std::cout << "Base" << std::endl; }
};
class Derived : public Base {
public:
    void print() override { std::cout << "Derived" << std::endl; }
};
int main() {
    Base* base = new Derived();
    Derived* derived = dynamic_cast<Derived*>(base); // 动态类型转换 / Dynamic type casting
    if (derived) {
        derived->print();
    }
    delete base;
    return 0;
} 