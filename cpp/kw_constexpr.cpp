// constexpr 示例 / Example
#include <iostream>
constexpr int square(int x) {
    return x * x;
}
constexpr int factorial(int n) {
    return (n <= 1) ? 1 : n * factorial(n - 1);
}
int main() {
    constexpr int result = square(5); // 编译期计算 / Compile-time calculation
    constexpr int fact = factorial(5);
    std::cout << "square(5) = " << result << std::endl;
    std::cout << "factorial(5) = " << fact << std::endl;
    return 0;
} 