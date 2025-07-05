// friend 示例 / Example
#include <iostream>
class MyClass {
private:
    int privateData;
public:
    MyClass(int data) : privateData(data) {}
    friend void friendFunction(MyClass& obj); // 友元函数 / Friend function
    friend class FriendClass; // 友元类 / Friend class
};
class FriendClass {
public:
    void accessPrivate(MyClass& obj) {
        std::cout << "Accessing private data: " << obj.privateData << std::endl;
    }
};
void friendFunction(MyClass& obj) {
    std::cout << "Friend function accessing: " << obj.privateData << std::endl;
}
int main() {
    MyClass obj(42);
    friendFunction(obj);
    FriendClass fc;
    fc.accessPrivate(obj);
    return 0;
} 