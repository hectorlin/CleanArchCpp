#include <iostream>
#include <vector>
#include <memory>

// Liskov Substitution Principle (LSP)
// Derived classes must be substitutable for their base classes

// Bad example: Violates LSP
class BadRectangle {
public:
    virtual void setWidth(double width) { this->width = width; }
    virtual void setHeight(double height) { this->height = height; }
    virtual double getWidth() const { return width; }
    virtual double getHeight() const { return height; }
    virtual double getArea() const { return width * height; }

protected:
    double width;
    double height;
};

class BadSquare : public BadRectangle {
public:
    void setWidth(double width) override {
        this->width = width;
        this->height = width; // This violates LSP!
    }
    
    void setHeight(double height) override {
        this->width = height; // This violates LSP!
        this->height = height;
    }
};

// Good example: Follows LSP
class Shape {
public:
    virtual ~Shape() = default;
    virtual double getArea() const = 0;
    virtual std::string getName() const = 0;
};

class Rectangle : public Shape {
public:
    Rectangle(double width, double height) : width(width), height(height) {}
    
    void setWidth(double width) { this->width = width; }
    void setHeight(double height) { this->height = height; }
    double getWidth() const { return width; }
    double getHeight() const { return height; }
    
    double getArea() const override { return width * height; }
    std::string getName() const override { return "Rectangle"; }

private:
    double width;
    double height;
};

class Square : public Shape {
public:
    Square(double side) : side(side) {}
    
    void setSide(double side) { this->side = side; }
    double getSide() const { return side; }
    
    double getArea() const override { return side * side; }
    std::string getName() const override { return "Square"; }

private:
    double side;
};

// Function that works with any Shape (LSP compliant)
void printShapeInfo(const Shape& shape) {
    std::cout << shape.getName() << " area: " << shape.getArea() << std::endl;
}

// Function that demonstrates LSP violation
void demonstrateLSPViolation() {
    std::cout << "\n--- LSP Violation Example ---" << std::endl;
    
    BadRectangle* rect = new BadRectangle();
    rect->setWidth(5);
    rect->setHeight(3);
    std::cout << "Rectangle area: " << rect->getArea() << std::endl;
    
    // Substituting with Square breaks the behavior
    BadSquare* square = new BadSquare();
    square->setWidth(5);
    square->setHeight(3); // This changes width too!
    std::cout << "Square area after setHeight(3): " << square->getArea() << std::endl;
    
    delete rect;
    delete square;
}

int main() {
    std::cout << "=== Liskov Substitution Principle (LSP) Example ===" << std::endl;
    
    // Demonstrate LSP violation
    demonstrateLSPViolation();
    
    // Good example: LSP compliant
    std::cout << "\n--- LSP Compliant Example ---" << std::endl;
    
    Rectangle rectangle(5, 3);
    Square square(4);
    
    // Both can be used polymorphically
    printShapeInfo(rectangle);
    printShapeInfo(square);
    
    // Vector of shapes (LSP compliant)
    std::vector<std::shared_ptr<Shape>> shapes;
    shapes.push_back(std::make_shared<Rectangle>(6, 4));
    shapes.push_back(std::make_shared<Square>(5));
    
    std::cout << "\nShapes in vector:" << std::endl;
    for (const auto& shape : shapes) {
        printShapeInfo(*shape);
    }
    
    return 0;
} 