#include <iostream>
#include <vector>
#include <memory>

// Open/Closed Principle (OCP)
// Software entities should be open for extension but closed for modification

// Bad example: Need to modify existing code to add new shapes
class BadShapeCalculator {
public:
    double calculateArea(const std::string& shapeType, double width, double height = 0) {
        if (shapeType == "rectangle") {
            return width * height;
        } else if (shapeType == "circle") {
            return 3.14159 * width * width; // width as radius
        }
        // Need to modify this class to add new shapes!
        return 0;
    }
};

// Good example: Open for extension, closed for modification
class Shape {
public:
    virtual ~Shape() = default;
    virtual double calculateArea() const = 0;
    virtual std::string getName() const = 0;
};

class Rectangle : public Shape {
public:
    Rectangle(double width, double height) : width(width), height(height) {}
    
    double calculateArea() const override {
        return width * height;
    }
    
    std::string getName() const override {
        return "Rectangle";
    }

private:
    double width;
    double height;
};

class Circle : public Shape {
public:
    Circle(double radius) : radius(radius) {}
    
    double calculateArea() const override {
        return 3.14159 * radius * radius;
    }
    
    std::string getName() const override {
        return "Circle";
    }

private:
    double radius;
};

// New shape can be added without modifying existing code
class Triangle : public Shape {
public:
    Triangle(double base, double height) : base(base), height(height) {}
    
    double calculateArea() const override {
        return 0.5 * base * height;
    }
    
    std::string getName() const override {
        return "Triangle";
    }

private:
    double base;
    double height;
};

class GoodShapeCalculator {
public:
    double calculateTotalArea(const std::vector<std::shared_ptr<Shape>>& shapes) {
        double totalArea = 0;
        for (const auto& shape : shapes) {
            totalArea += shape->calculateArea();
        }
        return totalArea;
    }
    
    void printShapeInfo(const std::vector<std::shared_ptr<Shape>>& shapes) {
        for (const auto& shape : shapes) {
            std::cout << shape->getName() << " area: " << shape->calculateArea() << std::endl;
        }
    }
};

int main() {
    std::cout << "=== Open/Closed Principle (OCP) Example ===" << std::endl;
    
    // Bad example
    std::cout << "\n--- Bad Example (Need to modify existing code) ---" << std::endl;
    BadShapeCalculator badCalc;
    std::cout << "Rectangle area: " << badCalc.calculateArea("rectangle", 5, 3) << std::endl;
    std::cout << "Circle area: " << badCalc.calculateArea("circle", 4) << std::endl;
    
    // Good example
    std::cout << "\n--- Good Example (Open for extension) ---" << std::endl;
    GoodShapeCalculator goodCalc;
    
    std::vector<std::shared_ptr<Shape>> shapes;
    shapes.push_back(std::make_shared<Rectangle>(5, 3));
    shapes.push_back(std::make_shared<Circle>(4));
    shapes.push_back(std::make_shared<Triangle>(6, 4)); // New shape without modifying existing code
    
    goodCalc.printShapeInfo(shapes);
    std::cout << "Total area: " << goodCalc.calculateTotalArea(shapes) << std::endl;
    
    return 0;
} 