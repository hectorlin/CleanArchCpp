// sizeof 示例 / Example
#include <iostream>
int main() {
    std::cout << "Size of int: " << sizeof(int) << " bytes" << std::endl;
    std::cout << "Size of double: " << sizeof(double) << " bytes" << std::endl;
    std::cout << "Size of char: " << sizeof(char) << " bytes" << std::endl;
    
    int arr[5];
    std::cout << "Size of array: " << sizeof(arr) << " bytes" << std::endl;
    std::cout << "Number of elements: " << sizeof(arr) / sizeof(arr[0]) << std::endl;
    return 0;
} 