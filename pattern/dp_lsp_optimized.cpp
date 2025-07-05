#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <functional>
#include <numeric>
#include <type_traits>

// Optimized Liskov Substitution Principle (LSP) Example
// Using modern C++17/20 features for better performance and type safety

// Bad example: Violating LSP
class BadRectangle {
public:
    virtual void setWidth(double width) { width_ = width; }
    virtual void setHeight(double height) { height_ = height; }
    [[nodiscard]] virtual double getWidth() const { return width_; }
    [[nodiscard]] virtual double getHeight() const { return height_; }
    [[nodiscard]] virtual double getArea() const { return width_ * height_; }

protected:
    double width_ = 0.0;
    double height_ = 0.0;
};

class BadSquare : public BadRectangle {
public:
    void setWidth(double width) override {
        width_ = height_ = width; // Violates LSP - changes both dimensions
    }
    
    void setHeight(double height) override {
        width_ = height_ = height; // Violates LSP - changes both dimensions
    }
};

// Optimized example: Following LSP with modern C++ features
class Shape {
public:
    virtual ~Shape() = default;
    [[nodiscard]] virtual double getArea() const = 0;
    [[nodiscard]] virtual double getPerimeter() const = 0;
    [[nodiscard]] virtual std::string getType() const = 0;
    
    // Common interface that works for all shapes
    virtual void resize(double factor) = 0;
    [[nodiscard]] virtual std::unique_ptr<Shape> clone() const = 0;
};

class Rectangle : public Shape {
public:
    Rectangle(double width, double height) 
        : width_(width), height_(height) {}
    
    [[nodiscard]] double getArea() const override {
        return width_ * height_;
    }
    
    [[nodiscard]] double getPerimeter() const override {
        return 2 * (width_ + height_);
    }
    
    [[nodiscard]] std::string getType() const override {
        return "Rectangle";
    }
    
    void resize(double factor) override {
        width_ *= factor;
        height_ *= factor;
    }
    
    [[nodiscard]] std::unique_ptr<Shape> clone() const override {
        return std::make_unique<Rectangle>(*this);
    }
    
    // Rectangle-specific methods
    void setWidth(double width) { width_ = width; }
    void setHeight(double height) { height_ = height; }
    [[nodiscard]] double getWidth() const noexcept { return width_; }
    [[nodiscard]] double getHeight() const noexcept { return height_; }

private:
    double width_;
    double height_;
};

class Square : public Shape {
public:
    explicit Square(double side) : side_(side) {}
    
    [[nodiscard]] double getArea() const override {
        return side_ * side_;
    }
    
    [[nodiscard]] double getPerimeter() const override {
        return 4 * side_;
    }
    
    [[nodiscard]] std::string getType() const override {
        return "Square";
    }
    
    void resize(double factor) override {
        side_ *= factor;
    }
    
    [[nodiscard]] std::unique_ptr<Shape> clone() const override {
        return std::make_unique<Square>(*this);
    }
    
    // Square-specific methods
    void setSide(double side) { side_ = side; }
    [[nodiscard]] double getSide() const noexcept { return side_; }

private:
    double side_;
};

// Modern shape processor that works with any shape
class ShapeProcessor {
public:
    // Generic shape operation using std::function
    using ShapeOperation = std::function<void(const Shape&)>;
    
    void addShape(std::unique_ptr<Shape> shape) {
        shapes_.push_back(std::move(shape));
    }
    
    // Process all shapes with any operation
    void processShapes(ShapeOperation operation) const {
        std::for_each(shapes_.begin(), shapes_.end(),
            [&operation](const auto& shape) { operation(*shape); });
    }
    
    // Calculate total area using std::accumulate
    [[nodiscard]] double calculateTotalArea() const {
        return std::accumulate(shapes_.begin(), shapes_.end(), 0.0,
            [](double sum, const auto& shape) { return sum + shape->getArea(); });
    }
    
    // Resize all shapes by factor
    void resizeAllShapes(double factor) {
        std::for_each(shapes_.begin(), shapes_.end(),
            [factor](auto& shape) { shape->resize(factor); });
    }
    
    // Clone all shapes
    [[nodiscard]] std::vector<std::unique_ptr<Shape>> cloneAllShapes() const {
        std::vector<std::unique_ptr<Shape>> clones;
        clones.reserve(shapes_.size());
        
        std::transform(shapes_.begin(), shapes_.end(), std::back_inserter(clones),
            [](const auto& shape) { return shape->clone(); });
        
        return clones;
    }
    
    // Get shapes by type using modern C++ features
    template<typename ShapeType>
    [[nodiscard]] std::vector<const ShapeType*> getShapesOfType() const {
        std::vector<const ShapeType*> result;
        std::copy_if(shapes_.begin(), shapes_.end(), std::back_inserter(result),
            [](const auto& shape) { 
                return dynamic_cast<const ShapeType*>(shape.get()) != nullptr; 
            });
        return result;
    }
    
    // Print all shapes with modern range-based for loop
    void printAllShapes() const {
        for (const auto& shape : shapes_) {
            std::cout << shape->getType() 
                      << " - Area: " << shape->getArea()
                      << ", Perimeter: " << shape->getPerimeter() << std::endl;
        }
    }

private:
    std::vector<std::unique_ptr<Shape>> shapes_;
};

// Template-based shape factory for compile-time type safety
template<typename ShapeType, typename... Args>
class ShapeFactory {
public:
    [[nodiscard]] static std::unique_ptr<Shape> create(Args&&... args) {
        return std::make_unique<ShapeType>(std::forward<Args>(args)...);
    }
};

// Modern shape validator that ensures LSP compliance
class ShapeValidator {
public:
    // Test if shapes can be substituted without breaking behavior
    [[nodiscard]] static bool testSubstitution(const Shape& shape) {
        try {
            // Test basic operations
            auto area = shape.getArea();
            auto perimeter = shape.getPerimeter();
            auto type = shape.getType();
            
            // Test cloning
            auto clone = shape.clone();
            if (!clone) return false;
            
            // Test that clone has same properties
            if (std::abs(clone->getArea() - area) > 1e-6) return false;
            if (std::abs(clone->getPerimeter() - perimeter) > 1e-6) return false;
            if (clone->getType() != type) return false;
            
            return true;
        } catch (...) {
            return false;
        }
    }
    
    // Test resize operation
    [[nodiscard]] static bool testResize(Shape& shape, double factor) {
        try {
            auto originalArea = shape.getArea();
            auto originalPerimeter = shape.getPerimeter();
            
            shape.resize(factor);
            
            auto newArea = shape.getArea();
            auto newPerimeter = shape.getPerimeter();
            
            // Check if resize worked correctly
            if (std::abs(newArea - originalArea * factor * factor) > 1e-6) return false;
            if (std::abs(newPerimeter - originalPerimeter * factor) > 1e-6) return false;
            
            return true;
        } catch (...) {
            return false;
        }
    }
};

int main() {
    std::cout << "=== Optimized Liskov Substitution Principle (LSP) Example ===" << std::endl;
    
    // Bad example: LSP violation
    std::cout << "\n--- Bad Example (LSP Violation) ---" << std::endl;
    BadRectangle* badRect = new BadRectangle();
    badRect->setWidth(5);
    badRect->setHeight(3);
    std::cout << "Rectangle area: " << badRect->getArea() << std::endl;
    
    BadRectangle* badSquare = new BadSquare();
    badSquare->setWidth(5);
    badSquare->setHeight(3); // This changes width too!
    std::cout << "Square area: " << badSquare->getArea() << std::endl;
    
    delete badRect;
    delete badSquare;
    
    // Optimized example: LSP compliance
    std::cout << "\n--- Optimized Example (LSP Compliant) ---" << std::endl;
    
    ShapeProcessor processor;
    
    // Add different shapes using modern factory pattern
    processor.addShape(std::make_unique<Rectangle>(5.0, 3.0));
    processor.addShape(std::make_unique<Square>(4.0));
    processor.addShape(std::make_unique<Rectangle>(2.0, 6.0));
    
    // Demonstrate LSP compliance - all shapes work with same interface
    std::cout << "Original shapes:" << std::endl;
    processor.printAllShapes();
    
    std::cout << "\nTotal area: " << processor.calculateTotalArea() << std::endl;
    
    // Test substitution with modern validation
    auto shapes = processor.cloneAllShapes();
    for (const auto& shape : shapes) {
        if (ShapeValidator::testSubstitution(*shape)) {
            std::cout << shape->getType() << " passes LSP test" << std::endl;
        } else {
            std::cout << shape->getType() << " fails LSP test" << std::endl;
        }
    }
    
    // Test resize operation
    std::cout << "\nResizing all shapes by factor 2:" << std::endl;
    processor.resizeAllShapes(2.0);
    processor.printAllShapes();
    
    // Demonstrate polymorphic behavior
    processor.processShapes([](const Shape& shape) {
        std::cout << "Processing " << shape.getType() 
                  << " with area " << shape.getArea() << std::endl;
    });
    
    return 0;
} 