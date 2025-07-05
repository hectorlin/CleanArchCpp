#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <functional>
#include <type_traits>
#include <any>

// Optimized Type Erasure Pattern Example
// Using modern C++17/20 features for better performance and type safety

// Bad example: Using void pointers (unsafe and error-prone)
class BadTypeEraser {
public:
    BadTypeEraser() : data_(nullptr), type_(nullptr) {}
    
    template<typename T>
    BadTypeEraser(const T& value) : data_(new T(value)), type_(&typeid(T)) {}
    
    ~BadTypeEraser() {
        if (data_) {
            // Problem: How do we know how to delete this?
            // We need to store the deleter function
            delete data_;
        }
    }
    
    template<typename T>
    T* get() {
        if (type_ && *type_ == typeid(T)) {
            return static_cast<T*>(data_);
        }
        return nullptr;
    }
    
    template<typename T>
    const T* get() const {
        if (type_ && *type_ == typeid(T)) {
            return static_cast<const T*>(data_);
        }
        return nullptr;
    }

private:
    void* data_;
    const std::type_info* type_;
};

// Optimized example: Type erasure with modern C++ features
// Using std::function and std::any for type safety

// Type traits for type erasure
template<typename T, typename = void>
struct is_printable : std::false_type {};

template<typename T>
struct is_printable<T, std::void_t<decltype(std::declval<T>().print())>> : std::true_type {};

template<typename T, typename = void>
struct is_calculable : std::false_type {};

template<typename T>
struct is_calculable<T, std::void_t<decltype(std::declval<T>().calculate(std::declval<int>()))>> : std::true_type {};

// Modern type erasure using std::function
class ModernTypeEraser {
public:
    // Default constructor
    ModernTypeEraser() = default;
    
    // Template constructor for any type
    template<typename T>
    ModernTypeEraser(T value) 
        : printFunc_([value = std::move(value)]() { value.print(); })
        , calculateFunc_([value = std::move(value)](int x) { return value.calculate(x); })
        , cloneFunc_([value = std::move(value)]() mutable { return ModernTypeEraser(std::move(value)); })
        , typeName_(typeid(T).name()) {}
    
    // Copy constructor
    ModernTypeEraser(const ModernTypeEraser& other) 
        : printFunc_(other.printFunc_)
        , calculateFunc_(other.calculateFunc_)
        , cloneFunc_(other.cloneFunc_)
        , typeName_(other.typeName_) {}
    
    // Copy assignment
    ModernTypeEraser& operator=(const ModernTypeEraser& other) {
        if (this != &other) {
            printFunc_ = other.printFunc_;
            calculateFunc_ = other.calculateFunc_;
            cloneFunc_ = other.cloneFunc_;
            typeName_ = other.typeName_;
        }
        return *this;
    }
    
    // Move constructor
    ModernTypeEraser(ModernTypeEraser&&) = default;
    
    // Move assignment
    ModernTypeEraser& operator=(ModernTypeEraser&&) = default;
    
    // Public interface
    void print() const {
        if (printFunc_) {
            printFunc_();
        }
    }
    
    [[nodiscard]] int calculate(int value) const {
        if (calculateFunc_) {
            return calculateFunc_(value);
        }
        return 0;
    }
    
    [[nodiscard]] ModernTypeEraser clone() const {
        if (cloneFunc_) {
            return cloneFunc_();
        }
        return ModernTypeEraser{};
    }
    
    [[nodiscard]] const std::string& getTypeName() const {
        return typeName_;
    }
    
    [[nodiscard]] bool isValid() const {
        return printFunc_ && calculateFunc_;
    }

private:
    std::function<void()> printFunc_;
    std::function<int(int)> calculateFunc_;
    std::function<ModernTypeEraser()> cloneFunc_;
    std::string typeName_;
};

// Example types that can be erased
class Calculator {
public:
    explicit Calculator(int multiplier) : multiplier_(multiplier) {}
    
    void print() const {
        std::cout << "Calculator with multiplier: " << multiplier_ << std::endl;
    }
    
    [[nodiscard]] int calculate(int value) const {
        return value * multiplier_;
    }

private:
    int multiplier_;
};

class Adder {
public:
    explicit Adder(int addend) : addend_(addend) {}
    
    void print() const {
        std::cout << "Adder with addend: " << addend_ << std::endl;
    }
    
    [[nodiscard]] int calculate(int value) const {
        return value + addend_;
    }

private:
    int addend_;
};

class Multiplier {
public:
    explicit Multiplier(int factor) : factor_(factor) {}
    
    void print() const {
        std::cout << "Multiplier with factor: " << factor_ << std::endl;
    }
    
    [[nodiscard]] int calculate(int value) const {
        return value * factor_;
    }

private:
    int factor_;
};

// Modern type erasure using std::any (C++17)
class AnyTypeEraser {
public:
    AnyTypeEraser() = default;
    
    template<typename T>
    AnyTypeEraser(T value) : data_(std::move(value)) {}
    
    template<typename T>
    [[nodiscard]] T* get() {
        return std::any_cast<T>(&data_);
    }
    
    template<typename T>
    [[nodiscard]] const T* get() const {
        return std::any_cast<const T>(&data_);
    }
    
    template<typename T>
    [[nodiscard]] T getValue() const {
        return std::any_cast<T>(data_);
    }
    
    [[nodiscard]] bool hasValue() const {
        return data_.has_value();
    }
    
    [[nodiscard]] const std::type_info& type() const {
        return data_.type();
    }

private:
    std::any data_;
};

// Type erasure with virtual interface
class IOperation {
public:
    virtual ~IOperation() = default;
    virtual void execute() = 0;
    virtual std::string getType() const = 0;
    [[nodiscard]] virtual std::unique_ptr<IOperation> clone() const = 0;
};

template<typename T>
class OperationWrapper : public IOperation {
public:
    explicit OperationWrapper(T operation) : operation_(std::move(operation)) {}
    
    void execute() override {
        operation_.execute();
    }
    
    std::string getType() const override {
        return operation_.getType();
    }
    
    [[nodiscard]] std::unique_ptr<IOperation> clone() const override {
        return std::make_unique<OperationWrapper>(operation_);
    }

private:
    T operation_;
};

// Example operations
class PrintOperation {
public:
    explicit PrintOperation(std::string message) : message_(std::move(message)) {}
    
    void execute() {
        std::cout << "Printing: " << message_ << std::endl;
    }
    
    [[nodiscard]] std::string getType() const {
        return "Print";
    }

private:
    std::string message_;
};

class MathOperation {
public:
    explicit MathOperation(int value) : value_(value) {}
    
    void execute() {
        std::cout << "Calculating with value: " << value_ << std::endl;
    }
    
    [[nodiscard]] std::string getType() const {
        return "Math";
    }

private:
    int value_;
};

// Modern type erasure container
class TypeErasureContainer {
public:
    template<typename T>
    void add(T value) {
        operations_.push_back(std::make_unique<OperationWrapper<T>>(std::move(value)));
    }
    
    void executeAll() {
        for (const auto& op : operations_) {
            op->execute();
        }
    }
    
    [[nodiscard]] size_t size() const {
        return operations_.size();
    }
    
    void clear() {
        operations_.clear();
    }
    
    // Type-safe access
    template<typename T>
    [[nodiscard]] std::vector<T*> getOperationsOfType() {
        std::vector<T*> result;
        for (const auto& op : operations_) {
            if (auto* wrapper = dynamic_cast<OperationWrapper<T>*>(op.get())) {
                result.push_back(&wrapper->getOperation());
            }
        }
        return result;
    }

private:
    std::vector<std::unique_ptr<IOperation>> operations_;
};

// Modern type erasure with concepts (C++20)
// Type trait for executable objects
template<typename T, typename = void>
struct is_executable : std::false_type {};

template<typename T>
struct is_executable<T, std::void_t<
    decltype(std::declval<T>().execute()),
    decltype(std::declval<T>().getType())
>> : std::true_type {};

template<typename T>
class ConceptBasedEraser {
    static_assert(is_executable<T>::value, "T must be executable");
public:
    explicit ConceptBasedEraser(T value) : value_(std::move(value)) {}
    
    void execute() {
        value_.execute();
    }
    
    [[nodiscard]] std::string getType() const {
        return value_.getType();
    }
    
    [[nodiscard]] const T& getValue() const {
        return value_;
    }

private:
    T value_;
};

// Modern type erasure with std::variant (C++17)
using VariantEraser = std::variant<Calculator, Adder, Multiplier>;

class VariantTypeEraser {
public:
    template<typename T>
    VariantTypeEraser(T value) : data_(std::move(value)) {}
    
    void print() const {
        std::visit([](const auto& value) { value.print(); }, data_);
    }
    
    [[nodiscard]] int calculate(int value) const {
        return std::visit([value](const auto& obj) { return obj.calculate(value); }, data_);
    }
    
    [[nodiscard]] std::string getTypeName() const {
        return std::visit([](const auto& obj) { return typeid(obj).name(); }, data_);
    }

private:
    VariantEraser data_;
};

// Modern type erasure with function objects
class FunctionTypeEraser {
public:
    template<typename T>
    FunctionTypeEraser(T value) 
        : printFunc_([value = std::move(value)]() { value.print(); })
        , calculateFunc_([value = std::move(value)](int x) { return value.calculate(x); })
        , typeFunc_([value = std::move(value)]() { return typeid(value).name(); }) {}
    
    void print() const {
        if (printFunc_) printFunc_();
    }
    
    [[nodiscard]] int calculate(int value) const {
        return calculateFunc_ ? calculateFunc_(value) : 0;
    }
    
    [[nodiscard]] std::string getTypeName() const {
        return typeFunc_ ? typeFunc_() : "Unknown";
    }

private:
    std::function<void()> printFunc_;
    std::function<int(int)> calculateFunc_;
    std::function<std::string()> typeFunc_;
};

int main() {
    std::cout << "=== Optimized Type Erasure Pattern Example ===" << std::endl;
    
    // Bad example: Void pointers
    std::cout << "\n--- Bad Example (Void Pointers) ---" << std::endl;
    BadTypeEraser badEraser(42);
    if (auto* value = badEraser.get<int>()) {
        std::cout << "Bad eraser value: " << *value << std::endl;
    }
    
    // Modern type erasure example
    std::cout << "\n--- Modern Type Erasure Example ---" << std::endl;
    
    ModernTypeEraser calcEraser(Calculator(5));
    ModernTypeEraser addEraser(Adder(10));
    ModernTypeEraser multEraser(Multiplier(3));
    
    calcEraser.print();
    std::cout << "Calculator result: " << calcEraser.calculate(7) << std::endl;
    
    addEraser.print();
    std::cout << "Adder result: " << addEraser.calculate(7) << std::endl;
    
    multEraser.print();
    std::cout << "Multiplier result: " << multEraser.calculate(7) << std::endl;
    
    // std::any type erasure
    std::cout << "\n--- std::any Type Erasure Example ---" << std::endl;
    
    AnyTypeEraser anyEraser{Calculator(4)};
    if (auto* calc = anyEraser.get<Calculator>()) {
        calc->print();
        std::cout << "Any eraser result: " << calc->calculate(6) << std::endl;
    }
    
    // Virtual interface type erasure
    std::cout << "\n--- Virtual Interface Type Erasure Example ---" << std::endl;
    
    TypeErasureContainer container;
    container.add(PrintOperation("Hello, Type Erasure!"));
    container.add(MathOperation(42));
    container.add(PrintOperation("Another message"));
    
    std::cout << "Container size: " << container.size() << std::endl;
    container.executeAll();
    
    // Variant-based type erasure
    std::cout << "\n--- Variant-based Type Erasure Example ---" << std::endl;
    
    VariantTypeEraser variantEraser(Calculator(6));
    variantEraser.print();
    std::cout << "Variant result: " << variantEraser.calculate(8) << std::endl;
    
    // Function-based type erasure
    std::cout << "\n--- Function-based Type Erasure Example ---" << std::endl;
    
    FunctionTypeEraser funcEraser(Adder(15));
    funcEraser.print();
    std::cout << "Function result: " << funcEraser.calculate(5) << std::endl;
    
    // Demonstrate type safety and cloning
    std::cout << "\n--- Type Safety and Cloning Demo ---" << std::endl;
    
    auto clonedEraser = calcEraser.clone();
    clonedEraser.print();
    std::cout << "Cloned result: " << clonedEraser.calculate(3) << std::endl;
    
    std::cout << "Original type: " << calcEraser.getTypeName() << std::endl;
    std::cout << "Cloned type: " << clonedEraser.getTypeName() << std::endl;
    
    return 0;
} 