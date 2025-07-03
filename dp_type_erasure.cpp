#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <functional>

// Type Erasure Pattern
// Runtime polymorphism without inheritance

// Concept: Drawable
class Drawable {
public:
    template<typename T>
    Drawable(T&& obj) : pImpl(std::make_unique<Model<T>>(std::forward<T>(obj))) {}
    
    Drawable(const Drawable& other) : pImpl(other.pImpl->clone()) {}
    Drawable& operator=(const Drawable& other) {
        pImpl = other.pImpl->clone();
        return *this;
    }
    
    Drawable(Drawable&&) = default;
    Drawable& operator=(Drawable&&) = default;
    
    void draw() const {
        pImpl->draw();
    }
    
private:
    struct Concept {
        virtual ~Concept() = default;
        virtual void draw() const = 0;
        virtual std::unique_ptr<Concept> clone() const = 0;
    };
    
    template<typename T>
    struct Model : Concept {
        Model(T&& obj) : object(std::forward<T>(obj)) {}
        
        void draw() const override {
            object.draw();
        }
        
        std::unique_ptr<Concept> clone() const override {
            return std::make_unique<Model<T>>(object);
        }
        
        T object;
    };
    
    std::unique_ptr<Concept> pImpl;
};

// Concrete types that don't inherit from a common base
class Circle {
public:
    Circle(double radius) : radius(radius) {}
    
    void draw() const {
        std::cout << "Drawing circle with radius: " << radius << std::endl;
    }
    
private:
    double radius;
};

class Rectangle {
public:
    Rectangle(double width, double height) : width(width), height(height) {}
    
    void draw() const {
        std::cout << "Drawing rectangle: " << width << "x" << height << std::endl;
    }
    
private:
    double width, height;
};

class Triangle {
public:
    Triangle(double base, double height) : base(base), height(height) {}
    
    void draw() const {
        std::cout << "Drawing triangle: base=" << base << ", height=" << height << std::endl;
    }
    
private:
    double base, height;
};

// Type erasure for callable objects
class Callable {
public:
    template<typename F>
    Callable(F&& f) : pImpl(std::make_unique<CallableModel<F>>(std::forward<F>(f))) {}
    
    Callable(const Callable& other) : pImpl(other.pImpl->clone()) {}
    Callable& operator=(const Callable& other) {
        pImpl = other.pImpl->clone();
        return *this;
    }
    
    Callable(Callable&&) = default;
    Callable& operator=(Callable&&) = default;
    
    template<typename... Args>
    auto operator()(Args&&... args) const {
        return pImpl->call(std::forward<Args>(args)...);
    }
    
private:
    struct CallableConcept {
        virtual ~CallableConcept() = default;
        virtual std::unique_ptr<CallableConcept> clone() const = 0;
        virtual int call(int x) const = 0;
    };
    
    template<typename F>
    struct CallableModel : CallableConcept {
        CallableModel(F&& f) : func(std::forward<F>(f)) {}
        
        std::unique_ptr<CallableConcept> clone() const override {
            return std::make_unique<CallableModel<F>>(func);
        }
        
        int call(int x) const override {
            return func(x);
        }
        
        F func;
    };
    
    std::unique_ptr<CallableConcept> pImpl;
};

// Type erasure for serializable objects
class Serializable {
public:
    template<typename T>
    Serializable(T&& obj) : pImpl(std::make_unique<SerializableModel<T>>(std::forward<T>(obj))) {}
    
    Serializable(const Serializable& other) : pImpl(other.pImpl->clone()) {}
    Serializable& operator=(const Serializable& other) {
        pImpl = other.pImpl->clone();
        return *this;
    }
    
    Serializable(Serializable&&) = default;
    Serializable& operator=(Serializable&&) = default;
    
    std::string serialize() const {
        return pImpl->serialize();
    }
    
private:
    struct SerializableConcept {
        virtual ~SerializableConcept() = default;
        virtual std::string serialize() const = 0;
        virtual std::unique_ptr<SerializableConcept> clone() const = 0;
    };
    
    template<typename T>
    struct SerializableModel : SerializableConcept {
        SerializableModel(T&& obj) : object(std::forward<T>(obj)) {}
        
        std::string serialize() const override {
            return object.serialize();
        }
        
        std::unique_ptr<SerializableConcept> clone() const override {
            return std::make_unique<SerializableModel<T>>(object);
        }
        
        T object;
    };
    
    std::unique_ptr<SerializableConcept> pImpl;
};

// Concrete serializable types
class User {
public:
    User(const std::string& name, int age) : name(name), age(age) {}
    
    std::string serialize() const {
        return "User{name='" + name + "', age=" + std::to_string(age) + "}";
    }
    
private:
    std::string name;
    int age;
};

class Product {
public:
    Product(const std::string& name, double price) : name(name), price(price) {}
    
    std::string serialize() const {
        return "Product{name='" + name + "', price=" + std::to_string(price) + "}";
    }
    
private:
    std::string name;
    double price;
};

int main() {
    std::cout << "=== Type Erasure Pattern Example ===" << std::endl;
    
    // Drawable type erasure
    std::cout << "\n--- Drawable Type Erasure ---" << std::endl;
    std::vector<Drawable> shapes;
    
    shapes.emplace_back(Circle(5.0));
    shapes.emplace_back(Rectangle(3.0, 4.0));
    shapes.emplace_back(Triangle(6.0, 4.0));
    
    for (const auto& shape : shapes) {
        shape.draw();
    }
    
    // Callable type erasure
    std::cout << "\n--- Callable Type Erasure ---" << std::endl;
    std::vector<Callable> functions;
    
    // Lambda function
    functions.emplace_back([](int x) { return x * 2; });
    
    // Function object
    struct Multiplier {
        int factor;
        Multiplier(int f) : factor(f) {}
        int operator()(int x) const { return x * factor; }
    };
    functions.emplace_back(Multiplier(3));
    
    // Function pointer
    int (*func_ptr)(int) = [](int x) { return x + 10; };
    functions.emplace_back(func_ptr);
    
    for (size_t i = 0; i < functions.size(); ++i) {
        std::cout << "Function " << i << "(5) = " << functions[i](5) << std::endl;
    }
    
    // Serializable type erasure
    std::cout << "\n--- Serializable Type Erasure ---" << std::endl;
    std::vector<Serializable> objects;
    
    objects.emplace_back(User("John Doe", 30));
    objects.emplace_back(Product("Laptop", 999.99));
    
    for (const auto& obj : objects) {
        std::cout << "Serialized: " << obj.serialize() << std::endl;
    }
    
    // Copying and moving type-erased objects
    std::cout << "\n--- Copying and Moving ---" << std::endl;
    
    Drawable original = Circle(10.0);
    Drawable copy = original; // Copy constructor
    Drawable moved = std::move(original); // Move constructor
    
    std::cout << "Original (moved): ";
    // original.draw(); // This would be invalid after move
    
    std::cout << "Copy: ";
    copy.draw();
    
    std::cout << "Moved: ";
    moved.draw();
    
    return 0;
} 