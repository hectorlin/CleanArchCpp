#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <type_traits>
#include <numeric>
#include <thread>

// Optimized CRTP (Curiously Recurring Template Pattern) Example
// Using modern C++17/20 features for better performance and type safety

// Bad example: Virtual functions with runtime overhead
class BadShape {
public:
    virtual ~BadShape() = default;
    virtual double getArea() const = 0;
    virtual double getPerimeter() const = 0;
    virtual std::string getType() const = 0;
};

class BadRectangle : public BadShape {
public:
    BadRectangle(double width, double height) : width_(width), height_(height) {}
    
    double getArea() const override {
        return width_ * height_;
    }
    
    double getPerimeter() const override {
        return 2 * (width_ + height_);
    }
    
    std::string getType() const override {
        return "Rectangle";
    }

private:
    double width_;
    double height_;
};

class BadCircle : public BadShape {
public:
    explicit BadCircle(double radius) : radius_(radius) {}
    
    double getArea() const override {
        return M_PI * radius_ * radius_;
    }
    
    double getPerimeter() const override {
        return 2 * M_PI * radius_;
    }
    
    std::string getType() const override {
        return "Circle";
    }

private:
    double radius_;
};

// Optimized example: CRTP with compile-time polymorphism
// Base class using CRTP
template<typename Derived>
class Shape {
public:
    [[nodiscard]] double getArea() const {
        return static_cast<const Derived*>(this)->getArea();
    }
    
    [[nodiscard]] double getPerimeter() const {
        return static_cast<const Derived*>(this)->getPerimeter();
    }
    
    [[nodiscard]] std::string getType() const {
        return static_cast<const Derived*>(this)->getType();
    }
    
    // Compile-time type checking
    [[nodiscard]] static constexpr bool isShape() {
        return std::is_base_of_v<Shape, Derived>;
    }
};

// Derived classes using CRTP
class Rectangle : public Shape<Rectangle> {
public:
    Rectangle(double width, double height) : width_(width), height_(height) {}
    
    [[nodiscard]] double getArea() const {
        return width_ * height_;
    }
    
    [[nodiscard]] double getPerimeter() const {
        return 2 * (width_ + height_);
    }
    
    [[nodiscard]] std::string getType() const {
        return "Rectangle";
    }
    
    // Rectangle-specific methods
    [[nodiscard]] double getWidth() const noexcept { return width_; }
    [[nodiscard]] double getHeight() const noexcept { return height_; }

private:
    double width_;
    double height_;
};

class Circle : public Shape<Circle> {
public:
    explicit Circle(double radius) : radius_(radius) {}
    
    [[nodiscard]] double getArea() const {
        return M_PI * radius_ * radius_;
    }
    
    [[nodiscard]] double getPerimeter() const {
        return 2 * M_PI * radius_;
    }
    
    [[nodiscard]] std::string getType() const {
        return "Circle";
    }
    
    // Circle-specific methods
    [[nodiscard]] double getRadius() const noexcept { return radius_; }

private:
    double radius_;
};

// Modern CRTP with additional features
template<typename Derived>
class ModernShape {
public:
    // Compile-time interface
    [[nodiscard]] double getArea() const {
        return derived().getArea();
    }
    
    [[nodiscard]] double getPerimeter() const {
        return derived().getPerimeter();
    }
    
    [[nodiscard]] std::string getType() const {
        return derived().getType();
    }
    
    // Modern CRTP features
    [[nodiscard]] bool isValid() const {
        return derived().isValid();
    }
    
    [[nodiscard]] double getVolume() const {
        return derived().getVolume();
    }
    
    // Static polymorphism
    template<typename OtherDerived>
    [[nodiscard]] bool hasSameArea(const ModernShape<OtherDerived>& other) const {
        return std::abs(getArea() - other.getArea()) < 1e-6;
    }
    
    // Type-safe comparison
    [[nodiscard]] bool operator==(const ModernShape& other) const {
        return derived() == other.derived();
    }

private:
    [[nodiscard]] const Derived& derived() const {
        return static_cast<const Derived&>(*this);
    }
    
    [[nodiscard]] Derived& derived() {
        return static_cast<Derived&>(*this);
    }
};

// Modern derived classes
class ModernRectangle : public ModernShape<ModernRectangle> {
public:
    ModernRectangle(double width, double height) : width_(width), height_(height) {}
    
    [[nodiscard]] double getArea() const {
        return width_ * height_;
    }
    
    [[nodiscard]] double getPerimeter() const {
        return 2 * (width_ + height_);
    }
    
    [[nodiscard]] std::string getType() const {
        return "ModernRectangle";
    }
    
    [[nodiscard]] bool isValid() const {
        return width_ > 0 && height_ > 0;
    }
    
    [[nodiscard]] double getVolume() const {
        return 0.0; // 2D shape
    }
    
    [[nodiscard]] bool operator==(const ModernRectangle& other) const {
        return std::abs(width_ - other.width_) < 1e-6 && 
               std::abs(height_ - other.height_) < 1e-6;
    }

private:
    double width_;
    double height_;
};

class ModernCircle : public ModernShape<ModernCircle> {
public:
    explicit ModernCircle(double radius) : radius_(radius) {}
    
    [[nodiscard]] double getArea() const {
        return M_PI * radius_ * radius_;
    }
    
    [[nodiscard]] double getPerimeter() const {
        return 2 * M_PI * radius_;
    }
    
    [[nodiscard]] std::string getType() const {
        return "ModernCircle";
    }
    
    [[nodiscard]] bool isValid() const {
        return radius_ > 0;
    }
    
    [[nodiscard]] double getVolume() const {
        return 0.0; // 2D shape
    }
    
    [[nodiscard]] bool operator==(const ModernCircle& other) const {
        return std::abs(radius_ - other.radius_) < 1e-6;
    }

private:
    double radius_;
};

// CRTP for object counting
template<typename T>
class ObjectCounter {
public:
    ObjectCounter() { ++count_; }
    ObjectCounter(const ObjectCounter&) { ++count_; }
    ObjectCounter(ObjectCounter&&) noexcept { ++count_; }
    ~ObjectCounter() { --count_; }
    
    ObjectCounter& operator=(const ObjectCounter&) = default;
    ObjectCounter& operator=(ObjectCounter&&) noexcept = default;
    
    [[nodiscard]] static size_t getCount() { return count_; }

private:
    static inline size_t count_ = 0;
};

// CRTP for singleton pattern
template<typename T>
class Singleton {
public:
    [[nodiscard]] static T& getInstance() {
        static T instance;
        return instance;
    }
    
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton(Singleton&&) = delete;
    Singleton& operator=(Singleton&&) = delete;

protected:
    Singleton() = default;
    ~Singleton() = default;
};

// Example singleton using CRTP
class Logger : public Singleton<Logger> {
public:
    void log(const std::string& message) {
        std::cout << "[LOG] " << message << std::endl;
    }
    
    void error(const std::string& message) {
        std::cerr << "[ERROR] " << message << std::endl;
    }

private:
    friend class Singleton<Logger>;
    Logger() = default;
};

// CRTP for static polymorphism with containers
template<typename Derived>
class Container {
public:
    using value_type = int; // Default value_type for containers
    void add(const value_type& item) {
        derived().add(item);
    }
    
    void remove(const value_type& item) {
        derived().remove(item);
    }
    
    [[nodiscard]] size_t size() const {
        return derived().size();
    }
    
    [[nodiscard]] bool empty() const {
        return derived().empty();
    }
    
    void clear() {
        derived().clear();
    }

private:
    [[nodiscard]] const Derived& derived() const {
        return static_cast<const Derived&>(*this);
    }
    
    [[nodiscard]] Derived& derived() {
        return static_cast<Derived&>(*this);
    }
};

// Modern container implementations
class ModernVector : public Container<ModernVector>, public ObjectCounter<ModernVector> {
public:
    using value_type = int;
    
    void add(const value_type& item) {
        data_.push_back(item);
    }
    
    void remove(const value_type& item) {
        auto it = std::find(data_.begin(), data_.end(), item);
        if (it != data_.end()) {
            data_.erase(it);
        }
    }
    
    [[nodiscard]] size_t size() const {
        return data_.size();
    }
    
    [[nodiscard]] bool empty() const {
        return data_.empty();
    }
    
    void clear() {
        data_.clear();
    }
    
    // Range-based for loop support
    [[nodiscard]] const std::vector<value_type>& getData() const {
        return data_;
    }

private:
    std::vector<value_type> data_;
};

// CRTP for performance measurement
template<typename Derived>
class PerformanceMeasurable {
public:
    void measureAndExecute() {
        auto start = std::chrono::high_resolution_clock::now();
        derived().execute();
        auto end = std::chrono::high_resolution_clock::now();
        
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "Execution time: " << duration.count() << " microseconds" << std::endl;
    }

private:
    [[nodiscard]] Derived& derived() {
        return static_cast<Derived&>(*this);
    }
};

class FastAlgorithm : public PerformanceMeasurable<FastAlgorithm> {
public:
    void execute() {
        // Simulate fast algorithm
        std::vector<int> data(1000);
        std::iota(data.begin(), data.end(), 0);
        std::sort(data.begin(), data.end());
    }
};

class SlowAlgorithm : public PerformanceMeasurable<SlowAlgorithm> {
public:
    void execute() {
        // Simulate slow algorithm
        std::vector<int> data(1000);
        std::iota(data.begin(), data.end(), 0);
        std::sort(data.begin(), data.end());
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
};

// Modern shape processor using CRTP
template<typename ShapeType>
class ShapeProcessor {
public:
    static void process(const ShapeType& shape) {
        std::cout << "Processing " << shape.getType() << std::endl;
        std::cout << "Area: " << shape.getArea() << std::endl;
        std::cout << "Perimeter: " << shape.getPerimeter() << std::endl;
        
        if constexpr (std::is_base_of_v<ModernShape<ShapeType>, ShapeType>) {
            std::cout << "Volume: " << shape.getVolume() << std::endl;
            std::cout << "Valid: " << (shape.isValid() ? "Yes" : "No") << std::endl;
        }
    }
    
    template<typename OtherShape>
    static void compare(const ShapeType& shape1, const OtherShape& shape2) {
        std::cout << "Comparing " << shape1.getType() << " and " << shape2.getType() << std::endl;
        std::cout << "Same area: " << (shape1.hasSameArea(shape2) ? "Yes" : "No") << std::endl;
    }
};

int main() {
    std::cout << "=== Optimized CRTP (Curiously Recurring Template Pattern) Example ===" << std::endl;
    
    // Bad example: Virtual functions
    std::cout << "\n--- Bad Example (Virtual Functions) ---" << std::endl;
    std::vector<std::unique_ptr<BadShape>> badShapes;
    badShapes.push_back(std::make_unique<BadRectangle>(5, 3));
    badShapes.push_back(std::make_unique<BadCircle>(2));
    
    for (const auto& shape : badShapes) {
        std::cout << shape->getType() << " - Area: " << shape->getArea() 
                  << ", Perimeter: " << shape->getPerimeter() << std::endl;
    }
    
    // Optimized example: CRTP with compile-time polymorphism
    std::cout << "\n--- Optimized Example (CRTP) ---" << std::endl;
    
    Rectangle rect(5, 3);
    Circle circle(2);
    
    std::cout << rect.getType() << " - Area: " << rect.getArea() 
              << ", Perimeter: " << rect.getPerimeter() << std::endl;
    std::cout << circle.getType() << " - Area: " << circle.getArea() 
              << ", Perimeter: " << circle.getPerimeter() << std::endl;
    
    // Modern CRTP example
    std::cout << "\n--- Modern CRTP Example ---" << std::endl;
    
    ModernRectangle modernRect(5, 3);
    ModernCircle modernCircle(2);
    
    ShapeProcessor<ModernRectangle>::process(modernRect);
    ShapeProcessor<ModernCircle>::process(modernCircle);
    
    ShapeProcessor<ModernRectangle>::compare(modernRect, modernCircle);
    
    // Object counting with CRTP
    std::cout << "\n--- Object Counting with CRTP ---" << std::endl;
    
    ModernVector vec1, vec2, vec3;
    vec1.add(1);
    vec2.add(2);
    vec3.add(3);
    
    std::cout << "ModernVector instances: " << ModernVector::getCount() << std::endl;
    
    // Singleton with CRTP
    std::cout << "\n--- Singleton with CRTP ---" << std::endl;
    
    auto& logger = Logger::getInstance();
    logger.log("Hello from CRTP singleton!");
    logger.error("This is an error message!");
    
    // Performance measurement with CRTP
    std::cout << "\n--- Performance Measurement with CRTP ---" << std::endl;
    
    FastAlgorithm fastAlgo;
    SlowAlgorithm slowAlgo;
    
    fastAlgo.measureAndExecute();
    slowAlgo.measureAndExecute();
    
    return 0;
} 