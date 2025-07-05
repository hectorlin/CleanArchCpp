// this 示例 / Example
#include <iostream>
class MyClass {
private:
    int value;
public:
    MyClass(int v) : value(v) {}
    MyClass& setValue(int v) {
        this->value = v; // 使用 this 指针 / Use this pointer
        return *this; // 返回当前对象引用 / Return reference to current object
    }
    void print() {
        std::cout << "Value: " << this->value << std::endl;
    }
};
int main() {
    MyClass obj(42);
    obj.setValue(100).print(); // 链式调用 / Method chaining
    return 0;
} 