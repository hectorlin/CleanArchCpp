#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>

// Optimized PIMPL (Pointer to Implementation) Idiom Example
// Using modern C++17/20 features for better performance and maintainability

// Bad example: Exposing implementation details in header
class BadPublicClass {
public:
    BadPublicClass();
    ~BadPublicClass();
    
    void doSomething();
    int calculate(int value);
    
    // Problem: Implementation details exposed
    std::vector<int> data_;           // Exposed implementation
    std::string name_;                // Exposed implementation
    double* cache_;                   // Exposed implementation
    size_t cacheSize_;                // Exposed implementation
    bool initialized_;                // Exposed implementation
};

// Optimized example: PIMPL idiom with modern C++ features

// Forward declaration of implementation class
class PublicClassImpl;

// Public interface class
class PublicClass {
public:
    // Constructor and destructor
    PublicClass();
    explicit PublicClass(std::string name);
    ~PublicClass();
    
    // Move semantics for better performance
    PublicClass(PublicClass&& other) noexcept;
    PublicClass& operator=(PublicClass&& other) noexcept;
    
    // Delete copy operations (or implement if needed)
    PublicClass(const PublicClass&) = delete;
    PublicClass& operator=(const PublicClass&) = delete;
    
    // Public interface methods
    void doSomething();
    [[nodiscard]] int calculate(int value);
    void addData(int value);
    [[nodiscard]] std::vector<int> getData() const;
    void setName(std::string name);
    [[nodiscard]] std::string getName() const;
    [[nodiscard]] size_t getDataSize() const;
    void clearData();
    [[nodiscard]] bool isInitialized() const;

private:
    // PIMPL: Pointer to implementation
    std::unique_ptr<PublicClassImpl> pImpl_;
};

// Implementation class (can be in separate .cpp file)
class PublicClassImpl {
public:
    PublicClassImpl() : initialized_(false), cacheSize_(0) {
        std::cout << "PublicClassImpl default constructed" << std::endl;
    }
    
    explicit PublicClassImpl(std::string name) 
        : name_(std::move(name)), initialized_(false), cacheSize_(0) {
        std::cout << "PublicClassImpl constructed with name: " << name_ << std::endl;
    }
    
    ~PublicClassImpl() {
        std::cout << "PublicClassImpl destructed: " << name_ << std::endl;
        delete[] cache_;
    }
    
    // Move semantics
    PublicClassImpl(PublicClassImpl&& other) noexcept
        : data_(std::move(other.data_))
        , name_(std::move(other.name_))
        , cache_(other.cache_)
        , cacheSize_(other.cacheSize_)
        , initialized_(other.initialized_) {
        other.cache_ = nullptr;
        other.cacheSize_ = 0;
        other.initialized_ = false;
        std::cout << "PublicClassImpl move constructed" << std::endl;
    }
    
    PublicClassImpl& operator=(PublicClassImpl&& other) noexcept {
        if (this != &other) {
            delete[] cache_;
            data_ = std::move(other.data_);
            name_ = std::move(other.name_);
            cache_ = other.cache_;
            cacheSize_ = other.cacheSize_;
            initialized_ = other.initialized_;
            other.cache_ = nullptr;
            other.cacheSize_ = 0;
            other.initialized_ = false;
            std::cout << "PublicClassImpl move assigned" << std::endl;
        }
        return *this;
    }
    
    // Delete copy operations
    PublicClassImpl(const PublicClassImpl&) = delete;
    PublicClassImpl& operator=(const PublicClassImpl&) = delete;
    
    // Implementation methods
    void doSomething() {
        if (!initialized_) {
            initialize();
        }
        std::cout << "PublicClassImpl doing something with " << data_.size() << " items" << std::endl;
    }
    
    [[nodiscard]] int calculate(int value) {
        if (!initialized_) {
            initialize();
        }
        
        // Use cache if available
        if (cache_ && value < static_cast<int>(cacheSize_)) {
            return cache_[value];
        }
        
        // Calculate and cache result
        int result = value * value + value * 2 + 1;
        
        // Expand cache if needed
        if (value >= static_cast<int>(cacheSize_)) {
            expandCache(value + 1);
        }
        
        if (cache_) {
            cache_[value] = result;
        }
        
        return result;
    }
    
    void addData(int value) {
        data_.push_back(value);
        std::cout << "Added data: " << value << std::endl;
    }
    
    [[nodiscard]] std::vector<int> getData() const {
        return data_;
    }
    
    void setName(std::string name) {
        name_ = std::move(name);
        std::cout << "Name set to: " << name_ << std::endl;
    }
    
    [[nodiscard]] std::string getName() const {
        return name_;
    }
    
    [[nodiscard]] size_t getDataSize() const {
        return data_.size();
    }
    
    void clearData() {
        data_.clear();
        std::cout << "Data cleared" << std::endl;
    }
    
    [[nodiscard]] bool isInitialized() const {
        return initialized_;
    }

private:
    void initialize() {
        std::cout << "Initializing PublicClassImpl: " << name_ << std::endl;
        initialized_ = true;
        cacheSize_ = 10;
        cache_ = new double[cacheSize_];
        std::fill(cache_, cache_ + cacheSize_, 0.0);
    }
    
    void expandCache(size_t newSize) {
        if (newSize <= cacheSize_) return;
        
        double* newCache = new double[newSize];
        std::fill(newCache, newCache + newSize, 0.0);
        
        if (cache_) {
            std::copy(cache_, cache_ + cacheSize_, newCache);
            delete[] cache_;
        }
        
        cache_ = newCache;
        cacheSize_ = newSize;
        std::cout << "Cache expanded to size: " << cacheSize_ << std::endl;
    }

private:
    std::vector<int> data_;
    std::string name_;
    double* cache_;
    size_t cacheSize_;
    bool initialized_;
};

// PublicClass implementation
PublicClass::PublicClass() : pImpl_(std::make_unique<PublicClassImpl>()) {}

PublicClass::PublicClass(std::string name) 
    : pImpl_(std::make_unique<PublicClassImpl>(std::move(name))) {}

PublicClass::~PublicClass() = default; // unique_ptr handles cleanup

PublicClass::PublicClass(PublicClass&& other) noexcept = default;
PublicClass& PublicClass::operator=(PublicClass&& other) noexcept = default;

void PublicClass::doSomething() {
    pImpl_->doSomething();
}

int PublicClass::calculate(int value) {
    return pImpl_->calculate(value);
}

void PublicClass::addData(int value) {
    pImpl_->addData(value);
}

std::vector<int> PublicClass::getData() const {
    return pImpl_->getData();
}

void PublicClass::setName(std::string name) {
    pImpl_->setName(std::move(name));
}

std::string PublicClass::getName() const {
    return pImpl_->getName();
}

size_t PublicClass::getDataSize() const {
    return pImpl_->getDataSize();
}

void PublicClass::clearData() {
    pImpl_->clearData();
}

bool PublicClass::isInitialized() const {
    return pImpl_->isInitialized();
}

// Modern PIMPL with template support
template<typename T>
class ModernPIMPL {
public:
    template<typename... Args>
    explicit ModernPIMPL(Args&&... args) 
        : pImpl_(std::make_unique<T>(std::forward<Args>(args)...)) {}
    
    ~ModernPIMPL() = default;
    
    // Move semantics
    ModernPIMPL(ModernPIMPL&&) = default;
    ModernPIMPL& operator=(ModernPIMPL&&) = default;
    
    // Delete copy operations
    ModernPIMPL(const ModernPIMPL&) = delete;
    ModernPIMPL& operator=(const ModernPIMPL&) = delete;
    
    // Access to implementation
    T* operator->() { return pImpl_.get(); }
    const T* operator->() const { return pImpl_.get(); }
    
    T& operator*() { return *pImpl_; }
    const T& operator*() const { return *pImpl_; }

private:
    std::unique_ptr<T> pImpl_;
};

// Example implementation class for template PIMPL
class AdvancedCalculator {
public:
    explicit AdvancedCalculator(std::string name) : name_(std::move(name)) {}
    
    [[nodiscard]] double add(double a, double b) const {
        return a + b;
    }
    
    [[nodiscard]] double multiply(double a, double b) const {
        return a * b;
    }
    
    [[nodiscard]] double power(double base, double exponent) const {
        return std::pow(base, exponent);
    }
    
    [[nodiscard]] std::string getName() const {
        return name_;
    }

private:
    std::string name_;
};

// Modern PIMPL with interface abstraction
class ICalculator {
public:
    virtual ~ICalculator() = default;
    virtual double calculate(double a, double b) = 0;
    virtual std::string getType() const = 0;
};

class AdditionCalculator : public ICalculator {
public:
    double calculate(double a, double b) override {
        return a + b;
    }
    
    std::string getType() const override {
        return "Addition";
    }
};

class MultiplicationCalculator : public ICalculator {
public:
    double calculate(double a, double b) override {
        return a * b;
    }
    
    std::string getType() const override {
        return "Multiplication";
    }
};

class CalculatorManager {
public:
    explicit CalculatorManager(std::unique_ptr<ICalculator> calculator)
        : calculator_(std::move(calculator)) {}
    
    double performCalculation(double a, double b) {
        return calculator_->calculate(a, b);
    }
    
    std::string getCalculatorType() const {
        return calculator_->getType();
    }

private:
    std::unique_ptr<ICalculator> calculator_;
};

int main() {
    std::cout << "=== Optimized PIMPL (Pointer to Implementation) Idiom Example ===" << std::endl;
    
    // Bad example: Exposed implementation
    std::cout << "\n--- Bad Example (Exposed Implementation) ---" << std::endl;
    BadPublicClass badClass;
    badClass.data_.push_back(42); // Direct access to implementation
    std::cout << "Bad class data size: " << badClass.data_.size() << std::endl;
    
    // Optimized example: PIMPL idiom
    std::cout << "\n--- Optimized Example (PIMPL Idiom) ---" << std::endl;
    
    PublicClass publicClass("TestClass");
    publicClass.addData(10);
    publicClass.addData(20);
    publicClass.addData(30);
    
    std::cout << "Data size: " << publicClass.getDataSize() << std::endl;
    std::cout << "Name: " << publicClass.getName() << std::endl;
    
    publicClass.doSomething();
    
    // Demonstrate calculation with caching
    std::cout << "Calculate(5): " << publicClass.calculate(5) << std::endl;
    std::cout << "Calculate(10): " << publicClass.calculate(10) << std::endl;
    std::cout << "Calculate(5) again: " << publicClass.calculate(5) << std::endl; // Should use cache
    
    // Demonstrate move semantics
    std::cout << "\n--- Move Semantics Demo ---" << std::endl;
    PublicClass movedClass = std::move(publicClass);
    std::cout << "Moved class name: " << movedClass.getName() << std::endl;
    std::cout << "Moved class data size: " << movedClass.getDataSize() << std::endl;
    
    // Template PIMPL example
    std::cout << "\n--- Template PIMPL Example ---" << std::endl;
    ModernPIMPL<AdvancedCalculator> calc("AdvancedCalc");
    
    std::cout << "Calculator name: " << calc->getName() << std::endl;
    std::cout << "Add(5, 3): " << calc->add(5, 3) << std::endl;
    std::cout << "Multiply(4, 7): " << calc->multiply(4, 7) << std::endl;
    std::cout << "Power(2, 8): " << calc->power(2, 8) << std::endl;
    
    // Interface-based PIMPL example
    std::cout << "\n--- Interface PIMPL Example ---" << std::endl;
    
    auto additionCalc = std::make_unique<AdditionCalculator>();
    CalculatorManager addManager(std::move(additionCalc));
    
    auto multiplicationCalc = std::make_unique<MultiplicationCalculator>();
    CalculatorManager multManager(std::move(multiplicationCalc));
    
    std::cout << "Addition calculator type: " << addManager.getCalculatorType() << std::endl;
    std::cout << "5 + 3 = " << addManager.performCalculation(5, 3) << std::endl;
    
    std::cout << "Multiplication calculator type: " << multManager.getCalculatorType() << std::endl;
    std::cout << "4 * 7 = " << multManager.performCalculation(4, 7) << std::endl;
    
    return 0;
} 