// template 示例 / Example
#include <iostream>
template<typename T>
T add(T a, T b) { // 函数模板 / Function template
    return a + b;
}
template<typename T>
class Container {
private:
    T data;
public:
    Container(T value) : data(value) {}
    T getValue() const { return data; }
};
int main() {
    std::cout << "add(5, 3) = " << add(5, 3) << std::endl;
    std::cout << "add(3.14, 2.86) = " << add(3.14, 2.86) << std::endl;
    
    Container<int> intContainer(42);
    Container<std::string> strContainer("Hello");
    
    std::cout << "intContainer: " << intContainer.getValue() << std::endl;
    std::cout << "strContainer: " << strContainer.getValue() << std::endl;
    return 0;
} 