// export 示例 / Example (保留关键字，C++11中已弃用 / Reserved keyword, deprecated in C++11)
#include <iostream>
// export template<typename T> void func(T); // 模板导出语法已弃用 / Template export syntax deprecated
int main() {
    std::cout << "export is a reserved keyword in C++11 / export 是 C++11 中的保留关键字" << std::endl;
    std::cout << "It was used for template export but is deprecated / 它用于模板导出但已弃用" << std::endl;
    return 0;
} 