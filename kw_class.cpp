// class 示例 / Example
#include <iostream>
class MyClass {
private:
    int x;
public:
    MyClass(int val) : x(val) {}
    void print() {
        std::cout << "x = " << x << std::endl;
    }
};
int main() {
    MyClass obj(42);
    obj.print();
    return 0;
} 