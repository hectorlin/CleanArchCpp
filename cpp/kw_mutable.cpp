// mutable 示例 / Example
#include <iostream>
class MyClass {
private:
    int data;
    mutable int cache; // 可变成员，即使在 const 函数中也可修改 / Mutable member
public:
    MyClass(int d) : data(d), cache(0) {}
    int getData() const {
        cache++; // 在 const 函数中修改 mutable 成员 / Modify mutable member in const function
        return data;
    }
    int getCache() const { return cache; }
};
int main() {
    const MyClass obj(42);
    std::cout << "Data: " << obj.getData() << std::endl;
    std::cout << "Cache: " << obj.getCache() << std::endl;
    return 0;
} 