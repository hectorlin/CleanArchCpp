#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <algorithm>

// Optimized Rule of Three/Five/Zero Example
// Using modern C++17/20 features for better performance and safety

// Bad example: Manual resource management without proper copy/move semantics
class BadResourceManager {
public:
    BadResourceManager(const std::string& name) : name_(name) {
        data_ = new int[100];
        std::cout << "BadResourceManager constructed: " << name_ << std::endl;
    }
    
    ~BadResourceManager() {
        delete[] data_;
        std::cout << "BadResourceManager destructed: " << name_ << std::endl;
    }
    
    // Problem: No copy constructor - shallow copy will cause double deletion
    // Problem: No copy assignment operator
    // Problem: No move constructor
    // Problem: No move assignment operator

private:
    std::string name_;
    int* data_;
};

// Rule of Three example (C++98/03 style)
class RuleOfThreeManager {
public:
    RuleOfThreeManager(const std::string& name) : name_(name) {
        data_ = new int[100];
        std::cout << "RuleOfThreeManager constructed: " << name_ << std::endl;
    }
    
    // Copy constructor (Rule of Three)
    RuleOfThreeManager(const RuleOfThreeManager& other) : name_(other.name_) {
        data_ = new int[100];
        std::copy(other.data_, other.data_ + 100, data_);
        std::cout << "RuleOfThreeManager copy constructed: " << name_ << std::endl;
    }
    
    // Copy assignment operator (Rule of Three)
    RuleOfThreeManager& operator=(const RuleOfThreeManager& other) {
        if (this != &other) {
            delete[] data_;
            name_ = other.name_;
            data_ = new int[100];
            std::copy(other.data_, other.data_ + 100, data_);
            std::cout << "RuleOfThreeManager copy assigned: " << name_ << std::endl;
        }
        return *this;
    }
    
    // Destructor (Rule of Three)
    ~RuleOfThreeManager() {
        delete[] data_;
        std::cout << "RuleOfThreeManager destructed: " << name_ << std::endl;
    }

private:
    std::string name_;
    int* data_;
};

// Rule of Five example (C++11 style)
class RuleOfFiveManager {
public:
    RuleOfFiveManager(const std::string& name) : name_(name) {
        data_ = new int[100];
        std::cout << "RuleOfFiveManager constructed: " << name_ << std::endl;
    }
    
    // Copy constructor
    RuleOfFiveManager(const RuleOfFiveManager& other) : name_(other.name_) {
        data_ = new int[100];
        std::copy(other.data_, other.data_ + 100, data_);
        std::cout << "RuleOfFiveManager copy constructed: " << name_ << std::endl;
    }
    
    // Copy assignment operator
    RuleOfFiveManager& operator=(const RuleOfFiveManager& other) {
        if (this != &other) {
            delete[] data_;
            name_ = other.name_;
            data_ = new int[100];
            std::copy(other.data_, other.data_ + 100, data_);
            std::cout << "RuleOfFiveManager copy assigned: " << name_ << std::endl;
        }
        return *this;
    }
    
    // Move constructor (Rule of Five)
    RuleOfFiveManager(RuleOfFiveManager&& other) noexcept 
        : name_(std::move(other.name_)), data_(other.data_) {
        other.data_ = nullptr;
        std::cout << "RuleOfFiveManager move constructed: " << name_ << std::endl;
    }
    
    // Move assignment operator (Rule of Five)
    RuleOfFiveManager& operator=(RuleOfFiveManager&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            name_ = std::move(other.name_);
            data_ = other.data_;
            other.data_ = nullptr;
            std::cout << "RuleOfFiveManager move assigned: " << name_ << std::endl;
        }
        return *this;
    }
    
    // Destructor
    ~RuleOfFiveManager() {
        delete[] data_;
        std::cout << "RuleOfFiveManager destructed: " << name_ << std::endl;
    }

private:
    std::string name_;
    int* data_;
};

// Rule of Zero example (Modern C++ style)
// Let the compiler generate everything automatically
class RuleOfZeroManager {
public:
    RuleOfZeroManager(std::string name) : name_(std::move(name)) {
        std::cout << "RuleOfZeroManager constructed: " << name_ << std::endl;
    }
    
    // No need to implement any of the five special member functions
    // Compiler will generate them automatically and correctly
    
    void doSomething() const {
        std::cout << "RuleOfZeroManager " << name_ << " doing something" << std::endl;
    }
    
    [[nodiscard]] const std::string& getName() const noexcept {
        return name_;
    }

private:
    std::string name_; // RAII-managed resource
};

// Modern resource manager using smart pointers (Rule of Zero)
class ModernResourceManager {
public:
    ModernResourceManager(std::string name, size_t size) 
        : name_(std::move(name)), data_(std::make_unique<int[]>(size)), size_(size) {
        std::cout << "ModernResourceManager constructed: " << name_ << std::endl;
    }
    
    // No need to implement any special member functions
    // unique_ptr handles all the resource management automatically
    
    void fillData() {
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = static_cast<int>(i);
        }
    }
    
    [[nodiscard]] int getValue(size_t index) const {
        if (index < size_) {
            return data_[index];
        }
        throw std::out_of_range("Index out of range");
    }
    
    void setValue(size_t index, int value) {
        if (index < size_) {
            data_[index] = value;
        } else {
            throw std::out_of_range("Index out of range");
        }
    }
    
    [[nodiscard]] size_t size() const noexcept {
        return size_;
    }
    
    [[nodiscard]] const std::string& getName() const noexcept {
        return name_;
    }

private:
    std::string name_;
    std::unique_ptr<int[]> data_;
    size_t size_;
};

// Modern container with RAII (Rule of Zero)
class ModernContainer {
public:
    ModernContainer() = default;
    
    void addItem(std::string item) {
        items_.push_back(std::move(item));
    }
    
    void removeItem(const std::string& item) {
        auto it = std::find(items_.begin(), items_.end(), item);
        if (it != items_.end()) {
            items_.erase(it);
        }
    }
    
    [[nodiscard]] bool contains(const std::string& item) const {
        return std::find(items_.begin(), items_.end(), item) != items_.end();
    }
    
    [[nodiscard]] size_t size() const noexcept {
        return items_.size();
    }
    
    // Range-based for loop support
    [[nodiscard]] const std::vector<std::string>& getItems() const noexcept {
        return items_;
    }

private:
    std::vector<std::string> items_; // RAII-managed container
};

// Modern factory using Rule of Zero
class ModernFactory {
public:
    // Create managers using modern C++ features
    [[nodiscard]] static ModernResourceManager createManager(std::string name, size_t size) {
        return ModernResourceManager(std::move(name), size);
    }
    
    [[nodiscard]] static ModernContainer createContainer() {
        return ModernContainer{};
    }
    
    // Template factory for any type
    template<typename T, typename... Args>
    [[nodiscard]] static T create(Args&&... args) {
        return T(std::forward<Args>(args)...);
    }
};

// Modern manager with move semantics optimization
class OptimizedManager {
public:
    OptimizedManager(std::string name) : name_(std::move(name)) {
        std::cout << "OptimizedManager constructed: " << name_ << std::endl;
    }
    
    // Explicitly default move operations for better performance
    OptimizedManager(OptimizedManager&&) = default;
    OptimizedManager& operator=(OptimizedManager&&) = default;
    
    // Delete copy operations if not needed
    OptimizedManager(const OptimizedManager&) = delete;
    OptimizedManager& operator=(const OptimizedManager&) = delete;
    
    void process() const {
        std::cout << "OptimizedManager " << name_ << " processing" << std::endl;
    }

private:
    std::string name_;
};

// Modern singleton using Rule of Zero (if singleton is really needed)
class ModernSingleton {
public:
    [[nodiscard]] static ModernSingleton& getInstance() {
        static ModernSingleton instance;
        return instance;
    }
    
    void doSomething() {
        std::cout << "ModernSingleton doing something" << std::endl;
    }
    
    // Delete copy and move operations
    ModernSingleton(const ModernSingleton&) = delete;
    ModernSingleton& operator=(const ModernSingleton&) = delete;
    ModernSingleton(ModernSingleton&&) = delete;
    ModernSingleton& operator=(ModernSingleton&&) = delete;

private:
    ModernSingleton() = default;
    ~ModernSingleton() = default;
};

int main() {
    std::cout << "=== Optimized Rule of Three/Five/Zero Example ===" << std::endl;
    
    // Bad example: No special member functions
    std::cout << "\n--- Bad Example (No Special Member Functions) ---" << std::endl;
    {
        BadResourceManager bad1("Bad1");
        // BadResourceManager bad2 = bad1; // This would cause problems!
    }
    
    // Rule of Three example
    std::cout << "\n--- Rule of Three Example ---" << std::endl;
    {
        RuleOfThreeManager three1("Three1");
        RuleOfThreeManager three2 = three1; // Copy constructor
        RuleOfThreeManager three3("Three3");
        three3 = three1; // Copy assignment
    }
    
    // Rule of Five example
    std::cout << "\n--- Rule of Five Example ---" << std::endl;
    {
        RuleOfFiveManager five1("Five1");
        RuleOfFiveManager five2 = five1; // Copy constructor
        RuleOfFiveManager five3 = std::move(five1); // Move constructor
        RuleOfFiveManager five4("Five4");
        five4 = std::move(five2); // Move assignment
    }
    
    // Rule of Zero example (Modern C++)
    std::cout << "\n--- Rule of Zero Example (Modern C++) ---" << std::endl;
    {
        RuleOfZeroManager zero1("Zero1");
        RuleOfZeroManager zero2 = zero1; // Automatic copy constructor
        RuleOfZeroManager zero3 = std::move(zero1); // Automatic move constructor
        RuleOfZeroManager zero4("Zero4");
        zero4 = std::move(zero2); // Automatic move assignment
    }
    
    // Modern resource manager example
    std::cout << "\n--- Modern Resource Manager Example ---" << std::endl;
    {
        ModernResourceManager manager1 = ModernFactory::createManager("Manager1", 100);
        manager1.fillData();
        
        ModernResourceManager manager2 = std::move(manager1); // Move semantics
        std::cout << "Manager2 name: " << manager2.getName() << std::endl;
        std::cout << "Manager2 size: " << manager2.size() << std::endl;
        std::cout << "Manager2 value at index 5: " << manager2.getValue(5) << std::endl;
    }
    
    // Modern container example
    std::cout << "\n--- Modern Container Example ---" << std::endl;
    {
        ModernContainer container = ModernFactory::createContainer();
        container.addItem("Item1");
        container.addItem("Item2");
        container.addItem("Item3");
        
        std::cout << "Container size: " << container.size() << std::endl;
        std::cout << "Contains Item2: " << (container.contains("Item2") ? "Yes" : "No") << std::endl;
        
        // Range-based for loop
        for (const auto& item : container.getItems()) {
            std::cout << "Item: " << item << std::endl;
        }
    }
    
    // Optimized manager example
    std::cout << "\n--- Optimized Manager Example ---" << std::endl;
    {
        OptimizedManager opt1("Opt1");
        OptimizedManager opt2 = std::move(opt1); // Move only
        opt2.process();
        
        // OptimizedManager opt3 = opt2; // This would not compile (copy deleted)
    }
    
    // Modern singleton example
    std::cout << "\n--- Modern Singleton Example ---" << std::endl;
    {
        auto& singleton = ModernSingleton::getInstance();
        singleton.doSomething();
    }
    
    return 0;
} 