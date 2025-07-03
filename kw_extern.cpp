// extern 示例 / Example
#include <iostream>
extern int globalVar; // 外部变量声明 / External variable declaration
extern "C" void cFunction(); // C 链接声明 / C linkage declaration
int main() {
    std::cout << "globalVar = " << globalVar << std::endl;
    return 0;
}
// 在另一个文件中定义 / Defined in another file
int globalVar = 42; 