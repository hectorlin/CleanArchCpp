// char16_t 和 char32_t 示例 / Example
#include <iostream>
int main() {
    char16_t c16 = u'中'; // 16位Unicode字符 / 16-bit Unicode character
    char32_t c32 = U'国'; // 32位Unicode字符 / 32-bit Unicode character
    std::cout << "char16_t: " << c16 << std::endl;
    std::cout << "char32_t: " << c32 << std::endl;
    return 0;
} 