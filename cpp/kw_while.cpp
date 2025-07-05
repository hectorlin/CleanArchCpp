// while 示例 / Example
#include <iostream>
int main() {
    int i = 0;
    while (i < 5) { // while 循环 / while loop
        std::cout << i << " ";
        ++i;
    }
    std::cout << std::endl;
    
    // do-while 循环 / do-while loop
    int j = 0;
    do {
        std::cout << j << " ";
        ++j;
    } while (j < 3);
    std::cout << std::endl;
    return 0;
} 