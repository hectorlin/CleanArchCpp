// throw 示例 / Example
#include <iostream>
#include <stdexcept>
void divide(int a, int b) {
    if (b == 0) {
        throw std::runtime_error("Division by zero / 除零错误"); // 抛出异常 / Throw exception
    }
    std::cout << "Result: " << a / b << std::endl;
}
int main() {
    try {
        divide(10, 2);
        divide(10, 0); // 这会抛出异常 / This will throw exception
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
    return 0;
} 