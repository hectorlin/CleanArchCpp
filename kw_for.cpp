// for 示例 / Example
#include <iostream>
#include <vector>
int main() {
    // 传统 for 循环 / Traditional for loop
    for (int i = 0; i < 5; ++i) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    
    // 基于范围的 for 循环 (C++11) / Range-based for loop (C++11)
    std::vector<int> vec = {1, 2, 3, 4, 5};
    for (const auto& item : vec) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
    return 0;
} 