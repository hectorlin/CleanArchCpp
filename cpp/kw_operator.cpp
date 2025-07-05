// operator 示例 / Example
#include <iostream>
class MyClass {
private:
    int value;
public:
    MyClass(int v) : value(v) {}
    MyClass operator+(const MyClass& other) const { // 重载加法运算符 / Overload addition operator
        return MyClass(value + other.value);
    }
    MyClass& operator++() { // 前缀递增运算符 / Prefix increment operator
        ++value;
        return *this;
    }
    MyClass operator++(int) { // 后缀递增运算符 / Postfix increment operator
        MyClass temp = *this;
        ++value;
        return temp;
    }
    int getValue() const { return value; }
};
int main() {
    MyClass a(5), b(3);
    MyClass c = a + b; // 使用重载的加法运算符 / Use overloaded addition operator
    std::cout << "c = " << c.getValue() << std::endl;
    ++c; // 前缀递增 / Prefix increment
    std::cout << "After ++c: " << c.getValue() << std::endl;
    return 0;
} 