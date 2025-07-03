// return 示例 / Example
#include <iostream>
int add(int a, int b) {
    return a + b; // 返回函数结果 / Return function result
}
void printMessage() {
    std::cout << "Hello World" << std::endl;
    return; // 从 void 函数返回 / Return from void function
}
int main() {
    int result = add(5, 3);
    std::cout << "Result: " << result << std::endl;
    printMessage();
    return 0; // 从 main 函数返回 / Return from main function
} 