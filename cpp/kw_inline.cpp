// inline 示例 / Example
#include <iostream>
inline int add(int a, int b) { // 内联函数 / Inline function
    return a + b;
}
class MyClass {
public:
    inline int multiply(int a, int b) { // 内联成员函数 / Inline member function
        return a * b;
    }
};
int main() {
    int result1 = add(5, 3);
    MyClass obj;
    int result2 = obj.multiply(4, 6);
    std::cout << "add(5, 3) = " << result1 << std::endl;
    std::cout << "multiply(4, 6) = " << result2 << std::endl;
    return 0;
} 