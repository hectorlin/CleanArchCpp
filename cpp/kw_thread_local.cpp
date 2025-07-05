// thread_local 示例 / Example
#include <iostream>
#include <thread>
thread_local int threadVar = 0; // 线程局部存储 / Thread local storage
void threadFunction(int id) {
    threadVar = id;
    std::cout << "Thread " << id << ": threadVar = " << threadVar << std::endl;
}
int main() {
    std::thread t1(threadFunction, 1);
    std::thread t2(threadFunction, 2);
    
    t1.join();
    t2.join();
    
    std::cout << "Main thread: threadVar = " << threadVar << std::endl;
    return 0;
} 