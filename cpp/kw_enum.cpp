// enum 示例 / Example
#include <iostream>
enum Color {
    RED,    // 0
    GREEN,  // 1
    BLUE    // 2
};
enum class Direction : int { // 强类型枚举 / Strongly typed enum
    NORTH = 0,
    SOUTH = 1,
    EAST = 2,
    WEST = 3
};
int main() {
    Color c = RED;
    Direction d = Direction::NORTH;
    std::cout << "Color: " << c << std::endl;
    std::cout << "Direction: " << static_cast<int>(d) << std::endl;
    return 0;
} 