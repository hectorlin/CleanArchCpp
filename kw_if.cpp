// if 示例 / Example
#include <iostream>
int main() {
    int x = 10;
    if (x > 5) {
        std::cout << "x is greater than 5 / x 大于 5" << std::endl;
    } else if (x == 5) {
        std::cout << "x equals 5 / x 等于 5" << std::endl;
    } else {
        std::cout << "x is less than 5 / x 小于 5" << std::endl;
    }
    return 0;
} 