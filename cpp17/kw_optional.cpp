#include <iostream>
#include <string>
#include <optional>
#include <vector>

// C++17: std::optional - 可选值
// C++17: std::optional - nullable values without pointers

// C++17 之前，需要使用指针或特殊值来表示"无值"
// Before C++17, you had to use pointers or special values to represent "no value"
// C++17 的 std::optional 提供了类型安全的解决方案
// C++17 std::optional provides a type-safe solution

// 可能返回值的函数
// Function that might return a value
std::optional<int> divide(int a, int b) {
    if (b == 0) {
        return std::nullopt;  // 无值
    }
    return a / b;  // 有值
}

// 可能返回字符串的函数
// Function that might return a string
std::optional<std::string> find_user(int id) {
    if (id == 1) {
        return "Alice";
    } else if (id == 2) {
        return "Bob";
    }
    return std::nullopt;  // 用户不存在
}

// 使用 optional 的类
// Class using optional
class User {
    std::string name_;
    std::optional<std::string> email_;
    std::optional<int> age_;
    
public:
    User(const std::string& name) : name_(name) {}
    
    void set_email(const std::string& email) {
        email_ = email;
    }
    
    void set_age(int age) {
        age_ = age;
    }
    
    void print_info() const {
        std::cout << "Name: " << name_ << std::endl;
        
        if (email_.has_value()) {
            std::cout << "Email: " << email_.value() << std::endl;
        } else {
            std::cout << "Email: Not provided" << std::endl;
        }
        
        if (age_.has_value()) {
            std::cout << "Age: " << age_.value() << std::endl;
        } else {
            std::cout << "Age: Not provided" << std::endl;
        }
    }
    
    // 使用 value_or 提供默认值
    // Using value_or to provide default values
    std::string get_email_or_default() const {
        return email_.value_or("no-email@example.com");
    }
    
    int get_age_or_default() const {
        return age_.value_or(-1);
    }
};

// 链式 optional 操作
// Chaining optional operations
std::optional<std::string> get_user_email(int user_id) {
    auto user = find_user(user_id);
    if (user.has_value()) {
        // 模拟获取邮箱
        // Simulate getting email
        if (user_id == 1) {
            return "alice@example.com";
        }
    }
    return std::nullopt;
}

// 使用 optional 的容器
// Container using optional
class Database {
    std::vector<std::optional<std::string>> records_;
    
public:
    void add_record(const std::string& record) {
        records_.push_back(record);
    }
    
    void add_empty_record() {
        records_.push_back(std::nullopt);
    }
    
    void print_records() const {
        for (size_t i = 0; i < records_.size(); ++i) {
            std::cout << "Record " << i << ": ";
            if (records_[i].has_value()) {
                std::cout << records_[i].value();
            } else {
                std::cout << "[EMPTY]";
            }
            std::cout << std::endl;
        }
    }
};

// 使用 optional 进行错误处理
// Using optional for error handling
struct Result {
    std::optional<int> value;
    std::optional<std::string> error;
    
    bool is_success() const {
        return value.has_value() && !error.has_value();
    }
};

Result safe_operation(int x, int y) {
    if (y == 0) {
        return {std::nullopt, "Division by zero"};
    }
    return {x / y, std::nullopt};
}

int main() {
    std::cout << "=== C++17 std::optional Demo ===" << std::endl;
    
    // 基本用法
    // Basic usage
    auto result1 = divide(10, 2);
    if (result1.has_value()) {
        std::cout << "10 / 2 = " << result1.value() << std::endl;
    }
    
    auto result2 = divide(10, 0);
    if (!result2.has_value()) {
        std::cout << "Division by zero: no result" << std::endl;
    }
    
    // 使用 value_or
    // Using value_or
    auto user1 = find_user(1);
    std::cout << "User 1: " << user1.value_or("Not found") << std::endl;
    
    auto user3 = find_user(3);
    std::cout << "User 3: " << user3.value_or("Not found") << std::endl;
    
    // 使用类
    // Using classes
    User alice("Alice");
    alice.set_email("alice@example.com");
    alice.set_age(25);
    alice.print_info();
    
    std::cout << "Email (with default): " << alice.get_email_or_default() << std::endl;
    std::cout << "Age (with default): " << alice.get_age_or_default() << std::endl;
    
    User bob("Bob");
    bob.print_info();
    std::cout << "Email (with default): " << bob.get_email_or_default() << std::endl;
    std::cout << "Age (with default): " << bob.get_age_or_default() << std::endl;
    
    // 链式操作
    // Chaining operations
    auto email = get_user_email(1);
    if (email.has_value()) {
        std::cout << "User 1 email: " << email.value() << std::endl;
    }
    
    auto email2 = get_user_email(3);
    if (!email2.has_value()) {
        std::cout << "User 3 email: Not found" << std::endl;
    }
    
    // 使用容器
    // Using containers
    Database db;
    db.add_record("Record 1");
    db.add_empty_record();
    db.add_record("Record 3");
    db.print_records();
    
    // 错误处理
    // Error handling
    auto op1 = safe_operation(10, 2);
    if (op1.is_success()) {
        std::cout << "Operation successful: " << op1.value.value() << std::endl;
    } else {
        std::cout << "Operation failed: " << op1.error.value() << std::endl;
    }
    
    auto op2 = safe_operation(10, 0);
    if (op2.is_success()) {
        std::cout << "Operation successful: " << op2.value.value() << std::endl;
    } else {
        std::cout << "Operation failed: " << op2.error.value() << std::endl;
    }
    
    // 直接构造 optional
    // Direct optional construction
    std::optional<int> opt1 = 42;
    std::optional<int> opt2 = std::nullopt;
    
    std::cout << "opt1 has value: " << opt1.has_value() << std::endl;
    std::cout << "opt2 has value: " << opt2.has_value() << std::endl;
    
    return 0;
} 