// struct 示例 / Example
#include <iostream>
struct Point {
    int x, y; // 默认公有成员 / Default public members
    Point(int x, int y) : x(x), y(y) {}
    void print() {
        std::cout << "Point(" << x << ", " << y << ")" << std::endl;
    }
};
int main() {
    Point p(10, 20);
    p.print();
    return 0;
} 