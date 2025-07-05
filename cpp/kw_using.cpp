// using 示例 / Example
#include <iostream>
#include <vector>
using namespace std; // 使用整个命名空间 / Use entire namespace
using std::string; // 使用特定类型 / Use specific type
template<typename T>
using Vector = std::vector<T>; // 类型别名 (C++11) / Type alias (C++11)
int main() {
    string str = "Hello"; // 不需要 std:: 前缀 / No need for std:: prefix
    Vector<int> vec = {1, 2, 3, 4, 5}; // 使用类型别名 / Use type alias
    
    cout << "str = " << str << endl;
    for (const auto& item : vec) {
        cout << item << " ";
    }
    cout << endl;
    return 0;
} 