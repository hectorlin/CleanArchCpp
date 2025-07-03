#include <iostream>
#include <string>
#include <memory>
#include <vector>

// PIMPL (Pointer to Implementation) Idiom
// Hide implementation details from the public interface

// Bad example: Implementation details exposed in header
class BadWidget {
public:
    BadWidget(const std::string& name);
    ~BadWidget();
    
    void doSomething();
    void setValue(int value);
    int getValue() const;
    
private:
    std::string name;
    int value;
    std::vector<int> internalData;
    bool isInitialized;
    void internalHelper();
    void validateState();
};

// Good example: PIMPL idiom
class Widget {
public:
    Widget(const std::string& name);
    ~Widget();
    
    // Copy constructor and assignment operator
    Widget(const Widget& other);
    Widget& operator=(const Widget& other);
    
    // Move constructor and assignment operator
    Widget(Widget&& other) noexcept;
    Widget& operator=(Widget&& other) noexcept;
    
    // Public interface
    void doSomething();
    void setValue(int value);
    int getValue() const;
    
private:
    class Impl; // Forward declaration
    std::unique_ptr<Impl> pImpl; // Pointer to implementation
};

// Implementation file (would be in .cpp file)
class Widget::Impl {
public:
    Impl(const std::string& name) : name(name), value(0), isInitialized(false) {
        internalData.reserve(100);
    }
    
    void doSomething() {
        if (!isInitialized) {
            initialize();
        }
        internalHelper();
        std::cout << "Widget '" << name << "' doing something with value: " << value << std::endl;
    }
    
    void setValue(int newValue) {
        value = newValue;
        validateState();
        std::cout << "Widget '" << name << "' value set to: " << value << std::endl;
    }
    
    int getValue() const {
        return value;
    }
    
private:
    std::string name;
    int value;
    std::vector<int> internalData;
    bool isInitialized;
    
    void initialize() {
        isInitialized = true;
        internalData.push_back(42);
        std::cout << "Widget '" << name << "' initialized" << std::endl;
    }
    
    void internalHelper() {
        // Complex internal logic
        for (int i = 0; i < 5; ++i) {
            internalData.push_back(i * value);
        }
    }
    
    void validateState() {
        if (value < 0) {
            value = 0;
            std::cout << "Value corrected to 0" << std::endl;
        }
    }
};

// Widget implementation
Widget::Widget(const std::string& name) : pImpl(std::make_unique<Impl>(name)) {}

Widget::~Widget() = default;

Widget::Widget(const Widget& other) : pImpl(std::make_unique<Impl>(*other.pImpl)) {}

Widget& Widget::operator=(const Widget& other) {
    if (this != &other) {
        pImpl = std::make_unique<Impl>(*other.pImpl);
    }
    return *this;
}

Widget::Widget(Widget&& other) noexcept = default;

Widget& Widget::operator=(Widget&& other) noexcept = default;

void Widget::doSomething() {
    pImpl->doSomething();
}

void Widget::setValue(int value) {
    pImpl->setValue(value);
}

int Widget::getValue() const {
    return pImpl->getValue();
}

// Another PIMPL example: Database connection
class DatabaseConnection {
public:
    DatabaseConnection(const std::string& connectionString);
    ~DatabaseConnection();
    
    DatabaseConnection(const DatabaseConnection& other);
    DatabaseConnection& operator=(const DatabaseConnection& other);
    
    DatabaseConnection(DatabaseConnection&& other) noexcept;
    DatabaseConnection& operator=(DatabaseConnection&& other) noexcept;
    
    bool connect();
    void disconnect();
    bool executeQuery(const std::string& query);
    bool isConnected() const;
    
private:
    class Impl;
    std::unique_ptr<Impl> pImpl;
};

class DatabaseConnection::Impl {
public:
    Impl(const std::string& connStr) : connectionString(connStr), connected(false) {}
    
    bool connect() {
        if (!connected) {
            // Simulate connection logic
            connected = true;
            std::cout << "Connected to: " << connectionString << std::endl;
        }
        return connected;
    }
    
    void disconnect() {
        if (connected) {
            connected = false;
            std::cout << "Disconnected from: " << connectionString << std::endl;
        }
    }
    
    bool executeQuery(const std::string& query) {
        if (connected) {
            std::cout << "Executing query: " << query << std::endl;
            return true;
        }
        return false;
    }
    
    bool isConnected() const {
        return connected;
    }
    
private:
    std::string connectionString;
    bool connected;
};

DatabaseConnection::DatabaseConnection(const std::string& connectionString) 
    : pImpl(std::make_unique<Impl>(connectionString)) {}

DatabaseConnection::~DatabaseConnection() = default;

DatabaseConnection::DatabaseConnection(const DatabaseConnection& other) 
    : pImpl(std::make_unique<Impl>(*other.pImpl)) {}

DatabaseConnection& DatabaseConnection::operator=(const DatabaseConnection& other) {
    if (this != &other) {
        pImpl = std::make_unique<Impl>(*other.pImpl);
    }
    return *this;
}

DatabaseConnection::DatabaseConnection(DatabaseConnection&& other) noexcept = default;

DatabaseConnection& DatabaseConnection::operator=(DatabaseConnection&& other) noexcept = default;

bool DatabaseConnection::connect() {
    return pImpl->connect();
}

void DatabaseConnection::disconnect() {
    pImpl->disconnect();
}

bool DatabaseConnection::executeQuery(const std::string& query) {
    return pImpl->executeQuery(query);
}

bool DatabaseConnection::isConnected() const {
    return pImpl->isConnected();
}

int main() {
    std::cout << "=== PIMPL (Pointer to Implementation) Idiom Example ===" << std::endl;
    
    // Widget example
    std::cout << "\n--- Widget Example ---" << std::endl;
    Widget widget1("MyWidget");
    widget1.setValue(42);
    widget1.doSomething();
    
    // Copying works correctly
    Widget widget2 = widget1;
    widget2.setValue(100);
    widget2.doSomething();
    
    // Moving works correctly
    Widget widget3 = std::move(widget1);
    widget3.doSomething();
    
    // Database connection example
    std::cout << "\n--- Database Connection Example ---" << std::endl;
    DatabaseConnection db1("localhost:5432/mydb");
    db1.connect();
    db1.executeQuery("SELECT * FROM users");
    
    // Copying database connection
    DatabaseConnection db2 = db1;
    db2.executeQuery("SELECT * FROM products");
    
    // Moving database connection
    DatabaseConnection db3 = std::move(db1);
    db3.executeQuery("SELECT * FROM orders");
    
    return 0;
} 