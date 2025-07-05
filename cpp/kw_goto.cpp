// goto 示例 / Example
#include <iostream>
int main() {
    int i = 0;
    start: // 标签 / Label
    if (i < 5) {
        std::cout << i << " ";
        ++i;
        goto start; // 跳转到标签 / Jump to label
    }
    std::cout << std::endl;
    return 0;
} 