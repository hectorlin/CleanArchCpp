#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <functional>
#include <numeric>
#include <variant>
#include <type_traits>

// Optimized Open/Closed Principle (OCP) Example
// Using modern C++17/20 features for extensibility and performance

// Bad example: Class that needs modification for new shapes
class BadShapeCalculator {
public:
    double calculateArea(const std::string& shapeType, double width, double height) {
        if (shapeType == "rectangle") {
            return width * height;
        } else if (shapeType == "circle") {
            return 3.14159 * width * width; // width as radius
        } else if (shapeType == "triangle") {
            return 0.5 * width * height;
        }
        return 0.0;
    }
};

// Optimized example: Open for extension, closed for modification
// Using modern C++ features for better performance and type safety

// Base shape interface with modern C++ features
class Shape {
public:
    virtual ~Shape() = default;
    [[nodiscard]] virtual double calculateArea() const = 0;
    [[nodiscard]] virtual double calculatePerimeter() const = 0;
    [[nodiscard]] virtual std::string getType() const = 0;
};

// Optimized concrete shapes with move semantics
class Rectangle : public Shape {
public:
    Rectangle(double width, double height) 
        : width_(width), height_(height) {}
    
    [[nodiscard]] double calculateArea() const override {
        return width_ * height_;
    }
    
    [[nodiscard]] double calculatePerimeter() const override {
        return 2 * (width_ + height_);
    }
    
    [[nodiscard]] std::string getType() const override {
        return "Rectangle";
    }
    
    // Getters with const correctness
    [[nodiscard]] double getWidth() const noexcept { return width_; }
    [[nodiscard]] double getHeight() const noexcept { return height_; }

private:
    double width_;
    double height_;
};

class Circle : public Shape {
public:
    explicit Circle(double radius) : radius_(radius) {}
    
    [[nodiscard]] double calculateArea() const override {
        return M_PI * radius_ * radius_;
    }
    
    [[nodiscard]] double calculatePerimeter() const override {
        return 2 * M_PI * radius_;
    }
    
    [[nodiscard]] std::string getType() const override {
        return "Circle";
    }
    
    [[nodiscard]] double getRadius() const noexcept { return radius_; }

private:
    double radius_;
};

class Triangle : public Shape {
public:
    Triangle(double base, double height) 
        : base_(base), height_(height) {}
    
    [[nodiscard]] double calculateArea() const override {
        return 0.5 * base_ * height_;
    }
    
    [[nodiscard]] double calculatePerimeter() const override {
        // Simplified perimeter calculation
        return base_ + height_ + std::sqrt(base_ * base_ + height_ * height_);
    }
    
    [[nodiscard]] std::string getType() const override {
        return "Triangle";
    }

private:
    double base_;
    double height_;
};

// Modern shape calculator using std::variant for type safety
class ModernShapeCalculator {
public:
    // Using std::function for flexible operations
    using ShapeOperation = std::function<double(const Shape&)>;
    
    void addShape(std::unique_ptr<Shape> shape) {
        shapes_.push_back(std::move(shape));
    }
    
    // Generic calculation method using std::function
    [[nodiscard]] std::vector<double> calculateForAllShapes(ShapeOperation operation) const {
        std::vector<double> results;
        results.reserve(shapes_.size()); // Pre-allocate for better performance
        
        std::transform(shapes_.begin(), shapes_.end(), std::back_inserter(results),
            [&operation](const auto& shape) { return operation(*shape); });
        
        return results;
    }
    
    // Optimized area calculation
    [[nodiscard]] std::vector<double> calculateAllAreas() const {
        return calculateForAllShapes([](const Shape& shape) { return shape.calculateArea(); });
    }
    
    // Optimized perimeter calculation
    [[nodiscard]] std::vector<double> calculateAllPerimeters() const {
        return calculateForAllShapes([](const Shape& shape) { return shape.calculatePerimeter(); });
    }
    
    // Total area calculation with std::accumulate
    [[nodiscard]] double calculateTotalArea() const {
        return std::accumulate(shapes_.begin(), shapes_.end(), 0.0,
            [](double sum, const auto& shape) { return sum + shape->calculateArea(); });
    }
    
    // Get shapes by type using modern C++ features
    [[nodiscard]] std::vector<const Shape*> getShapesByType(const std::string& type) const {
        std::vector<const Shape*> result;
        for (const auto& shape : shapes_) {
            if (shape->getType() == type) {
                result.push_back(shape.get());
            }
        }
        return result;
    }
    
    // Print all shapes with modern range-based for loop
    void printAllShapes() const {
        for (const auto& shape : shapes_) {
            std::cout << shape->getType() 
                      << " - Area: " << shape->calculateArea()
                      << ", Perimeter: " << shape->calculatePerimeter() << std::endl;
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

// Modern shape processor with visitor pattern
class ShapeProcessor {
public:
    // Process shapes with custom visitor function
    template<typename Visitor>
    void processShapes(const std::vector<std::unique_ptr<Shape>>& shapes, Visitor visitor) {
        std::for_each(shapes.begin(), shapes.end(),
            [&visitor](const auto& shape) { visitor(*shape); });
    }
    
    // Calculate statistics
    struct ShapeStats {
        double totalArea = 0.0;
        double totalPerimeter = 0.0;
        size_t count = 0;
    };
    
    [[nodiscard]] ShapeStats calculateStats(const std::vector<std::unique_ptr<Shape>>& shapes) const {
        return std::accumulate(shapes.begin(), shapes.end(), ShapeStats{},
            [](ShapeStats stats, const auto& shape) {
                stats.totalArea += shape->calculateArea();
                stats.totalPerimeter += shape->calculatePerimeter();
                stats.count++;
                return stats;
            });
    }
};

int main() {
    std::cout << "=== Optimized Open/Closed Principle (OCP) Example ===" << std::endl;
    
    // Bad example
    std::cout << "\n--- Bad Example (Needs Modification) ---" << std::endl;
    BadShapeCalculator badCalc;
    std::cout << "Rectangle area: " << badCalc.calculateArea("rectangle", 5, 3) << std::endl;
    std::cout << "Circle area: " << badCalc.calculateArea("circle", 2, 0) << std::endl;
    
    // Optimized example
    std::cout << "\n--- Optimized Example (Open for Extension) ---" << std::endl;
    
    ModernShapeCalculator calculator;
    
    // Add shapes using modern factory pattern
    calculator.addShape(std::make_unique<Rectangle>(5.0, 3.0));
    calculator.addShape(std::make_unique<Circle>(2.0));
    calculator.addShape(std::make_unique<Triangle>(4.0, 3.0));
    
    // Demonstrate extensibility - add new shape without modifying existing code
    class Square : public Shape {
    public:
        explicit Square(double side) : side_(side) {}
        
        [[nodiscard]] double calculateArea() const override {
            return side_ * side_;
        }
        
        [[nodiscard]] double calculatePerimeter() const override {
            return 4 * side_;
        }
        
        [[nodiscard]] std::string getType() const override {
            return "Square";
        }
    private:
        double side_;
    };
    
    calculator.addShape(std::make_unique<Square>(4.0));
    
    // Use optimized calculation methods
    auto areas = calculator.calculateAllAreas();
    auto perimeters = calculator.calculateAllPerimeters();
    
    std::cout << "Areas: ";
    for (double area : areas) {
        std::cout << area << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Perimeters: ";
    for (double perimeter : perimeters) {
        std::cout << perimeter << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Total area: " << calculator.calculateTotalArea() << std::endl;
    
    // Demonstrate modern processing
    ShapeProcessor processor;
    processor.processShapes(std::vector<std::unique_ptr<Shape>>{}, 
        [](const Shape& shape) {
            std::cout << "Processing " << shape.getType() << std::endl;
        });
    
    calculator.printAllShapes();
    
    return 0;
} 