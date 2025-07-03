// break 示例 / Example
#include <iostream>
int main() {
    for (int i = 0; i < 10; ++i) {
        if (i == 5) break; // 跳出循环 / Break the loop
        std::cout << i << " ";
    }
    std::cout << std::endl;
    return 0;
} 