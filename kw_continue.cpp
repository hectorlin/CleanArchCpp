// continue 示例 / Example
#include <iostream>
int main() {
    for (int i = 0; i < 10; ++i) {
        if (i % 2 == 0) {
            continue; // 跳过偶数 / Skip even numbers
        }
        std::cout << i << " ";
    }
    std::cout << std::endl;
    return 0;
} 