// new 示例 / Example
#include <iostream>
int main() {
    int* ptr1 = new int(42); // 动态分配单个整数 / Dynamic allocation of single integer
    int* arr = new int[5]{1, 2, 3, 4, 5}; // 动态分配数组 / Dynamic allocation of array
    
    std::cout << "*ptr1 = " << *ptr1 << std::endl;
    for (int i = 0; i < 5; ++i) {
        std::cout << "arr[" << i << "] = " << arr[i] << std::endl;
    }
    
    delete ptr1; // 释放单个对象 / Delete single object
    delete[] arr; // 释放数组 / Delete array
    return 0;
} 