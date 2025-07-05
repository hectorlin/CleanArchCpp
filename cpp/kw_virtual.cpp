// virtual 示例 / Example
#include <iostream>
class Base {
public:
    virtual void print() { // 虚函数 / Virtual function
        std::cout << "Base::print() / 基类打印" << std::endl;
    }
    virtual ~Base() = default; // 虚析构函数 / Virtual destructor
};
class Derived : public Base {
public:
    void print() override { // 重写虚函数 / Override virtual function
        std::cout << "Derived::print() / 派生类打印" << std::endl;
    }
};
int main() {
    Base* ptr = new Derived();
    ptr->print(); // 调用派生类的函数 / Call derived class function
    delete ptr;
    return 0;
} 