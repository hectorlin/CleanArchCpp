// typename 示例 / Example
#include <iostream>
#include <vector>
template<typename T>
class Container {
public:
    typedef typename std::vector<T>::iterator iterator; // 使用 typename 指定依赖类型 / Use typename for dependent types
    typedef typename std::vector<T>::const_iterator const_iterator;
    
    std::vector<T> data;
    
    iterator begin() { return data.begin(); }
    const_iterator begin() const { return data.begin(); }
};
int main() {
    Container<int> container;
    container.data.push_back(1);
    container.data.push_back(2);
    
    for (Container<int>::iterator it = container.begin(); it != container.data.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    return 0;
} 