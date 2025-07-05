#include <iostream>
#include <string>
#include <vector>
#include <memory>

// CRTP (Curiously Recurring Template Pattern)
// Static polymorphism using templates

// Base class using CRTP
template<typename Derived>
class Base {
public:
    void interface() {
        static_cast<Derived*>(this)->implementation();
    }
    
    void commonFunction() {
        std::cout << "Common functionality in base class" << std::endl;
    }
    
    // Static polymorphism - resolved at compile time
    static void staticInterface() {
        Derived::staticImplementation();
    }
    
    // CRTP for object counting
    static size_t getCount() {
        return count;
    }
    
protected:
    Base() { ++count; }
    ~Base() { --count; }
    
private:
    static size_t count;
};

template<typename Derived>
size_t Base<Derived>::count = 0;

// Derived classes
class Derived1 : public Base<Derived1> {
public:
    void implementation() {
        std::cout << "Derived1 implementation" << std::endl;
    }
    
    static void staticImplementation() {
        std::cout << "Derived1 static implementation" << std::endl;
    }
};

class Derived2 : public Base<Derived2> {
public:
    void implementation() {
        std::cout << "Derived2 implementation" << std::endl;
    }
    
    static void staticImplementation() {
        std::cout << "Derived2 static implementation" << std::endl;
    }
};

// CRTP for object comparison
template<typename Derived>
class Comparable {
public:
    bool operator==(const Derived& other) const {
        return static_cast<const Derived*>(this)->equals(other);
    }
    
    bool operator!=(const Derived& other) const {
        return !(*this == other);
    }
};

class Point : public Comparable<Point> {
public:
    Point(int x, int y) : x(x), y(y) {}
    
    bool equals(const Point& other) const {
        return x == other.x && y == other.y;
    }
    
    int getX() const { return x; }
    int getY() const { return y; }
    
private:
    int x, y;
};

// CRTP for singleton pattern
template<typename Derived>
class Singleton {
public:
    static Derived& getInstance() {
        static Derived instance;
        return instance;
    }
    
protected:
    Singleton() = default;
    ~Singleton() = default;
    
private:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
};

class Logger : public Singleton<Logger> {
public:
    void log(const std::string& message) {
        std::cout << "Log: " << message << std::endl;
    }
    
private:
    friend class Singleton<Logger>;
    Logger() = default;
};

// CRTP for object cloning
template<typename Derived>
class Cloneable {
public:
    std::unique_ptr<Derived> clone() const {
        return std::unique_ptr<Derived>(static_cast<Derived*>(cloneImpl()));
    }
    
protected:
    virtual Cloneable* cloneImpl() const = 0;
};

class Shape : public Cloneable<Shape> {
public:
    virtual ~Shape() = default;
    virtual void draw() const = 0;
    
protected:
    virtual Shape* cloneImpl() const override = 0;
};

class Circle : public Shape {
public:
    Circle(double radius) : radius(radius) {}
    
    void draw() const override {
        std::cout << "Drawing circle with radius: " << radius << std::endl;
    }
    
    double getRadius() const { return radius; }
    
protected:
    Circle* cloneImpl() const override {
        return new Circle(*this);
    }
    
private:
    double radius;
};

class Rectangle : public Shape {
public:
    Rectangle(double width, double height) : width(width), height(height) {}
    
    void draw() const override {
        std::cout << "Drawing rectangle: " << width << "x" << height << std::endl;
    }
    
    double getWidth() const { return width; }
    double getHeight() const { return height; }
    
protected:
    Rectangle* cloneImpl() const override {
        return new Rectangle(*this);
    }
    
private:
    double width, height;
};

// CRTP for numeric operations
template<typename Derived>
class Numeric {
public:
    Derived operator+(const Derived& other) const {
        return Derived(static_cast<const Derived*>(this)->value() + other.value());
    }
    
    Derived operator-(const Derived& other) const {
        return Derived(static_cast<const Derived*>(this)->value() - other.value());
    }
    
    bool operator<(const Derived& other) const {
        return static_cast<const Derived*>(this)->value() < other.value();
    }
};

class Integer : public Numeric<Integer> {
public:
    Integer(int val) : val(val) {}
    
    int value() const { return val; }
    
    friend std::ostream& operator<<(std::ostream& os, const Integer& i) {
        return os << i.val;
    }
    
private:
    int val;
};

int main() {
    std::cout << "=== CRTP (Curiously Recurring Template Pattern) Example ===" << std::endl;
    
    // Basic CRTP example
    std::cout << "\n--- Basic CRTP Example ---" << std::endl;
    Derived1 d1;
    Derived2 d2;
    
    d1.interface(); // Calls Derived1::implementation
    d2.interface(); // Calls Derived2::implementation
    
    Derived1::staticInterface(); // Static polymorphism
    Derived2::staticInterface();
    
    // Object counting with CRTP
    std::cout << "\n--- Object Counting ---" << std::endl;
    std::cout << "Derived1 count: " << Derived1::getCount() << std::endl;
    std::cout << "Derived2 count: " << Derived2::getCount() << std::endl;
    
    {
        Derived1 temp1, temp2;
        std::cout << "Derived1 count after creating 2 objects: " << Derived1::getCount() << std::endl;
    }
    std::cout << "Derived1 count after scope: " << Derived1::getCount() << std::endl;
    
    // Comparable CRTP example
    std::cout << "\n--- Comparable CRTP Example ---" << std::endl;
    Point p1(1, 2);
    Point p2(1, 2);
    Point p3(3, 4);
    
    std::cout << "p1 == p2: " << (p1 == p2) << std::endl;
    std::cout << "p1 == p3: " << (p1 == p3) << std::endl;
    std::cout << "p1 != p3: " << (p1 != p3) << std::endl;
    
    // Singleton CRTP example
    std::cout << "\n--- Singleton CRTP Example ---" << std::endl;
    Logger::getInstance().log("First message");
    Logger::getInstance().log("Second message");
    
    // Cloneable CRTP example
    std::cout << "\n--- Cloneable CRTP Example ---" << std::endl;
    std::unique_ptr<Shape> circle = std::make_unique<Circle>(5.0);
    std::unique_ptr<Shape> rect = std::make_unique<Rectangle>(3.0, 4.0);
    
    circle->draw();
    rect->draw();
    
    // Clone the shapes
    auto circleClone = circle->clone();
    auto rectClone = rect->clone();
    
    circleClone->draw();
    rectClone->draw();
    
    // Numeric CRTP example
    std::cout << "\n--- Numeric CRTP Example ---" << std::endl;
    Integer a(5);
    Integer b(3);
    
    Integer c = a + b;
    Integer d = a - b;
    
    std::cout << "a = " << a << ", b = " << b << std::endl;
    std::cout << "a + b = " << c << std::endl;
    std::cout << "a - b = " << d << std::endl;
    std::cout << "a < b: " << (a < b) << std::endl;
    
    return 0;
} 