// union 示例 / Example
#include <iostream>
union Data {
    int i;
    float f;
    char str[20];
};
int main() {
    Data data;
    data.i = 42;
    std::cout << "data.i = " << data.i << std::endl;
    
    data.f = 3.14f;
    std::cout << "data.f = " << data.f << std::endl;
    
    strcpy(data.str, "Hello");
    std::cout << "data.str = " << data.str << std::endl;
    return 0;
} 