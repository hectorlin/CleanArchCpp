#include <iostream>
#include <string>
#include <memory>

// Rule of Three/Five/Zero
// If you need to implement any of destructor, copy constructor, or copy assignment operator,
// you probably need to implement all three (Rule of Three)
// In C++11, this extends to move constructor and move assignment operator (Rule of Five)
// Rule of Zero: Prefer to use standard library types that handle resource management

// Bad example: Rule of Three violation
class BadResourceManager {
private:
    int* data;
    size_t size;

public:
    BadResourceManager(size_t s) : size(s) {
        data = new int[size];
        std::cout << "Constructor: Allocated " << size << " integers" << std::endl;
    }
    
    // Destructor
    ~BadResourceManager() {
        delete[] data;
        std::cout << "Destructor: Deallocated " << size << " integers" << std::endl;
    }
    
    // Problem: No copy constructor - will cause double deletion
    // Problem: No copy assignment operator - will cause double deletion
    
    void setValue(size_t index, int value) {
        if (index < size) {
            data[index] = value;
        }
    }
    
    int getValue(size_t index) const {
        if (index < size) {
            return data[index];
        }
        return 0;
    }
};

// Good example: Rule of Three implementation
class GoodResourceManager {
private:
    int* data;
    size_t size;

public:
    // Constructor
    GoodResourceManager(size_t s) : size(s) {
        data = new int[size];
        std::cout << "Constructor: Allocated " << size << " integers" << std::endl;
    }
    
    // Copy constructor (Rule of Three)
    GoodResourceManager(const GoodResourceManager& other) : size(other.size) {
        data = new int[size];
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
        std::cout << "Copy constructor: Copied " << size << " integers" << std::endl;
    }
    
    // Copy assignment operator (Rule of Three)
    GoodResourceManager& operator=(const GoodResourceManager& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new int[size];
            for (size_t i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
            std::cout << "Copy assignment: Copied " << size << " integers" << std::endl;
        }
        return *this;
    }
    
    // Destructor (Rule of Three)
    ~GoodResourceManager() {
        delete[] data;
        std::cout << "Destructor: Deallocated " << size << " integers" << std::endl;
    }
    
    void setValue(size_t index, int value) {
        if (index < size) {
            data[index] = value;
        }
    }
    
    int getValue(size_t index) const {
        if (index < size) {
            return data[index];
        }
        return 0;
    }
};

// Better example: Rule of Five (C++11)
class BetterResourceManager {
private:
    int* data;
    size_t size;

public:
    // Constructor
    BetterResourceManager(size_t s) : size(s) {
        data = new int[size];
        std::cout << "Constructor: Allocated " << size << " integers" << std::endl;
    }
    
    // Copy constructor
    BetterResourceManager(const BetterResourceManager& other) : size(other.size) {
        data = new int[size];
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
        std::cout << "Copy constructor: Copied " << size << " integers" << std::endl;
    }
    
    // Move constructor (Rule of Five)
    BetterResourceManager(BetterResourceManager&& other) noexcept 
        : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
        std::cout << "Move constructor: Moved " << size << " integers" << std::endl;
    }
    
    // Copy assignment operator
    BetterResourceManager& operator=(const BetterResourceManager& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new int[size];
            for (size_t i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
            std::cout << "Copy assignment: Copied " << size << " integers" << std::endl;
        }
        return *this;
    }
    
    // Move assignment operator (Rule of Five)
    BetterResourceManager& operator=(BetterResourceManager&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;
            other.data = nullptr;
            other.size = 0;
            std::cout << "Move assignment: Moved " << size << " integers" << std::endl;
        }
        return *this;
    }
    
    // Destructor
    ~BetterResourceManager() {
        delete[] data;
        std::cout << "Destructor: Deallocated " << size << " integers" << std::endl;
    }
    
    void setValue(size_t index, int value) {
        if (index < size) {
            data[index] = value;
        }
    }
    
    int getValue(size_t index) const {
        if (index < size) {
            return data[index];
        }
        return 0;
    }
};

// Best example: Rule of Zero (prefer standard library)
class BestResourceManager {
private:
    std::unique_ptr<int[]> data;
    size_t size;

public:
    BestResourceManager(size_t s) 
        : data(std::make_unique<int[]>(s)), size(s) {
        std::cout << "Constructor: Allocated " << size << " integers" << std::endl;
    }
    
    // No need to implement copy/move constructors or assignment operators
    // std::unique_ptr handles resource management automatically
    
    void setValue(size_t index, int value) {
        if (index < size) {
            data[index] = value;
        }
    }
    
    int getValue(size_t index) const {
        if (index < size) {
            return data[index];
        }
        return 0;
    }
};

// Example showing the problems with Rule of Three violation
void demonstrateRuleViolation() {
    std::cout << "\n--- Rule of Three Violation ---" << std::endl;
    
    BadResourceManager bad1(3);
    bad1.setValue(0, 42);
    
    // This will cause problems - no copy constructor
    BadResourceManager bad2 = bad1; // Double deletion will occur!
    
    std::cout << "Value: " << bad2.getValue(0) << std::endl;
}

int main() {
    std::cout << "=== Rule of Three/Five/Zero Example ===" << std::endl;
    
    // Rule of Three implementation
    std::cout << "\n--- Rule of Three Implementation ---" << std::endl;
    {
        GoodResourceManager good1(3);
        good1.setValue(0, 42);
        
        GoodResourceManager good2 = good1; // Copy constructor
        std::cout << "Copied value: " << good2.getValue(0) << std::endl;
        
        GoodResourceManager good3(2);
        good3 = good1; // Copy assignment
        std::cout << "Assigned value: " << good3.getValue(0) << std::endl;
    }
    
    // Rule of Five implementation
    std::cout << "\n--- Rule of Five Implementation ---" << std::endl;
    {
        BetterResourceManager better1(3);
        better1.setValue(0, 42);
        
        BetterResourceManager better2 = std::move(better1); // Move constructor
        std::cout << "Moved value: " << better2.getValue(0) << std::endl;
        
        BetterResourceManager better3(2);
        better3 = std::move(better2); // Move assignment
        std::cout << "Move assigned value: " << better3.getValue(0) << std::endl;
    }
    
    // Rule of Zero implementation
    std::cout << "\n--- Rule of Zero Implementation ---" << std::endl;
    {
        BestResourceManager best1(3);
        best1.setValue(0, 42);
        
        // std::unique_ptr automatically prevents copying
        // BestResourceManager best2 = best1; // This won't compile - good!
        
        // But we can move it
        BestResourceManager best2 = std::move(best1);
        std::cout << "Moved value: " << best2.getValue(0) << std::endl;
    }
    
    return 0;
} 