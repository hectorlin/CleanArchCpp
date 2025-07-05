// volatile 示例 / Example
#include <iostream>
volatile int sharedVariable = 0; // 易变变量 / Volatile variable
void updateVariable() {
    sharedVariable = 42; // 修改易变变量 / Modify volatile variable
}
int main() {
    std::cout << "Initial value: " << sharedVariable << std::endl;
    updateVariable();
    std::cout << "After update: " << sharedVariable << std::endl;
    return 0;
} 