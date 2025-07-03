// typedef 示例 / Example
#include <iostream>
typedef int Integer; // 类型别名 / Type alias
typedef int* IntPtr; // 指针类型别名 / Pointer type alias
typedef int Array[5]; // 数组类型别名 / Array type alias
int main() {
    Integer x = 42;
    IntPtr ptr = &x;
    Array arr = {1, 2, 3, 4, 5};
    
    std::cout << "x = " << x << std::endl;
    std::cout << "*ptr = " << *ptr << std::endl;
    std::cout << "arr[0] = " << arr[0] << std::endl;
    return 0;
} 