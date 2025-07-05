// switch 示例 / Example
#include <iostream>
int main() {
    int choice = 2;
    switch (choice) {
        case 1:
            std::cout << "Choice 1 / 选择 1" << std::endl;
            break;
        case 2:
            std::cout << "Choice 2 / 选择 2" << std::endl;
            break;
        case 3:
            std::cout << "Choice 3 / 选择 3" << std::endl;
            break;
        default:
            std::cout << "Default choice / 默认选择" << std::endl;
            break;
    }
    return 0;
} 