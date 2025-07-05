// catch 示例 / Example
#include <iostream>
int main() {
    try {
        throw 1;
    } catch (int e) {
        std::cout << "Caught exception: " << e << " / 捕获异常" << std::endl;
    }
    return 0;
} 