// alignas 示例 / Example
//
//
//
#include <iostream>
struct alignas(16) AlignedStruct {
    int x;
};
int main() {
    AlignedStruct a;
    std::cout << "Address: " << &a << std::endl;
    std::cout << "alignof(AlignedStruct): " << alignof(AlignedStruct) << std::endl;
    return 0;
} 