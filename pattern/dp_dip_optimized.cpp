#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <functional>
#include <type_traits>

// Optimized Dependency Inversion Principle (DIP) Example
// Using modern C++17/20 features for better performance and type safety

// Bad example: High-level modules depend on low-level modules
class BadMySQLDatabase {
public:
    void save(const std::string& data) {
        std::cout << "Saving to MySQL: " << data << std::endl;
    }
    
    std::string load(const std::string& id) {
        std::cout << "Loading from MySQL: " << id << std::endl;
        return "Data from MySQL";
    }
};

class BadUserService {
public:
    BadUserService() : database_(std::make_unique<BadMySQLDatabase>()) {}
    
    void createUser(const std::string& name) {
        database_->save("User: " + name);
    }
    
    std::string getUser(const std::string& id) {
        return database_->load(id);
    }

private:
    std::unique_ptr<BadMySQLDatabase> database_; // Direct dependency on concrete class
};

// Optimized example: Depend on abstractions, not concretions
// Using modern C++ features for better performance and flexibility

// Abstract database interface
class DatabaseInterface {
public:
    virtual ~DatabaseInterface() = default;
    virtual void save(const std::string& data) = 0;
    virtual std::string load(const std::string& id) = 0;
    [[nodiscard]] virtual bool isConnected() const = 0;
    virtual void connect() = 0;
    virtual void disconnect() = 0;
};

// Abstract logger interface
class LoggerInterface {
public:
    virtual ~LoggerInterface() = default;
    virtual void log(const std::string& message) = 0;
    virtual void error(const std::string& error) = 0;
    virtual void warn(const std::string& warning) = 0;
    [[nodiscard]] virtual std::string getLogLevel() const = 0;
};

// Abstract notification interface
class NotificationInterface {
public:
    virtual ~NotificationInterface() = default;
    virtual void sendNotification(const std::string& message) = 0;
    virtual void sendEmail(const std::string& to, const std::string& subject, const std::string& body) = 0;
    [[nodiscard]] virtual bool isAvailable() const = 0;
};

// Concrete database implementations
class MySQLDatabase : public DatabaseInterface {
public:
    MySQLDatabase() : connected_(false) {}
    
    void save(const std::string& data) override {
        if (!connected_) connect();
        std::cout << "Saving to MySQL: " << data << std::endl;
    }
    
    std::string load(const std::string& id) override {
        if (!connected_) connect();
        std::cout << "Loading from MySQL: " << id << std::endl;
        return "Data from MySQL";
    }
    
    [[nodiscard]] bool isConnected() const override { return connected_; }
    
    void connect() override {
        std::cout << "Connecting to MySQL..." << std::endl;
        connected_ = true;
    }
    
    void disconnect() override {
        std::cout << "Disconnecting from MySQL..." << std::endl;
        connected_ = false;
    }

private:
    bool connected_;
};

class PostgreSQLDatabase : public DatabaseInterface {
public:
    PostgreSQLDatabase() : connected_(false) {}
    
    void save(const std::string& data) override {
        if (!connected_) connect();
        std::cout << "Saving to PostgreSQL: " << data << std::endl;
    }
    
    std::string load(const std::string& id) override {
        if (!connected_) connect();
        std::cout << "Loading from PostgreSQL: " << id << std::endl;
        return "Data from PostgreSQL";
    }
    
    [[nodiscard]] bool isConnected() const override { return connected_; }
    
    void connect() override {
        std::cout << "Connecting to PostgreSQL..." << std::endl;
        connected_ = true;
    }
    
    void disconnect() override {
        std::cout << "Disconnecting from PostgreSQL..." << std::endl;
        connected_ = false;
    }

private:
    bool connected_;
};

// Concrete logger implementations
class ConsoleLogger : public LoggerInterface {
public:
    void log(const std::string& message) override {
        std::cout << "[INFO] " << message << std::endl;
    }
    
    void error(const std::string& error) override {
        std::cerr << "[ERROR] " << error << std::endl;
    }
    
    void warn(const std::string& warning) override {
        std::cout << "[WARN] " << warning << std::endl;
    }
    
    [[nodiscard]] std::string getLogLevel() const override { return "INFO"; }
};

class FileLogger : public LoggerInterface {
public:
    void log(const std::string& message) override {
        std::cout << "[FILE] " << message << std::endl;
    }
    
    void error(const std::string& error) override {
        std::cout << "[FILE ERROR] " << error << std::endl;
    }
    
    void warn(const std::string& warning) override {
        std::cout << "[FILE WARN] " << warning << std::endl;
    }
    
    [[nodiscard]] std::string getLogLevel() const override { return "DEBUG"; }
};

// Concrete notification implementations
class EmailNotification : public NotificationInterface {
public:
    void sendNotification(const std::string& message) override {
        std::cout << "Sending email notification: " << message << std::endl;
    }
    
    void sendEmail(const std::string& to, const std::string& subject, const std::string& body) override {
        std::cout << "Sending email to " << to << " - Subject: " << subject << std::endl;
        std::cout << "Body: " << body << std::endl;
    }
    
    [[nodiscard]] bool isAvailable() const override { return true; }
};

class SMSNotification : public NotificationInterface {
public:
    void sendNotification(const std::string& message) override {
        std::cout << "Sending SMS notification: " << message << std::endl;
    }
    
    void sendEmail(const std::string& to, const std::string& subject, const std::string& body) override {
        std::cout << "SMS doesn't support email, sending SMS instead" << std::endl;
        sendNotification(body);
    }
    
    [[nodiscard]] bool isAvailable() const override { return true; }
};

// Optimized high-level service using dependency injection
class UserService {
public:
    // Constructor injection with modern C++ features
    UserService(std::shared_ptr<DatabaseInterface> db,
                std::shared_ptr<LoggerInterface> logger,
                std::shared_ptr<NotificationInterface> notifier)
        : database_(std::move(db))
        , logger_(std::move(logger))
        , notifier_(std::move(notifier)) {}
    
    // Create user with comprehensive logging and notification
    void createUser(const std::string& name, const std::string& email) {
        try {
            logger_->log("Creating user: " + name);
            
            if (!database_->isConnected()) {
                database_->connect();
            }
            
            database_->save("User: " + name + ", Email: " + email);
            
            logger_->log("User created successfully: " + name);
            
            if (notifier_->isAvailable()) {
                notifier_->sendEmail(email, "Welcome!", "Welcome to our system, " + name + "!");
            }
            
        } catch (const std::exception& e) {
            logger_->error("Failed to create user: " + std::string(e.what()));
            throw;
        }
    }
    
    // Get user with error handling
    [[nodiscard]] std::string getUser(const std::string& id) {
        try {
            logger_->log("Retrieving user: " + id);
            
            if (!database_->isConnected()) {
                database_->connect();
            }
            
            auto userData = database_->load(id);
            logger_->log("User retrieved successfully: " + id);
            
            return userData;
            
        } catch (const std::exception& e) {
            logger_->error("Failed to retrieve user: " + std::string(e.what()));
            throw;
        }
    }
    
    // Batch operations with modern C++ features
    void createUsers(const std::vector<std::pair<std::string, std::string>>& users) {
        logger_->log("Creating " + std::to_string(users.size()) + " users");
        
        std::for_each(users.begin(), users.end(),
            [this](const auto& user) {
                createUser(user.first, user.second);
            });
    }
    
    // Get all users (simplified)
    [[nodiscard]] std::vector<std::string> getAllUsers() {
        std::vector<std::string> users;
        // In real implementation, this would query the database
        users.push_back(database_->load("user1"));
        users.push_back(database_->load("user2"));
        return users;
    }

private:
    std::shared_ptr<DatabaseInterface> database_;
    std::shared_ptr<LoggerInterface> logger_;
    std::shared_ptr<NotificationInterface> notifier_;
};

// Modern service factory using dependency injection
class ServiceFactory {
public:
    // Create service with MySQL and console logging
    [[nodiscard]] static std::unique_ptr<UserService> createMySQLService() {
        auto db = std::make_shared<MySQLDatabase>();
        auto logger = std::make_shared<ConsoleLogger>();
        auto notifier = std::make_shared<EmailNotification>();
        
        return std::make_unique<UserService>(db, logger, notifier);
    }
    
    // Create service with PostgreSQL and file logging
    [[nodiscard]] static std::unique_ptr<UserService> createPostgreSQLService() {
        auto db = std::make_shared<PostgreSQLDatabase>();
        auto logger = std::make_shared<FileLogger>();
        auto notifier = std::make_shared<SMSNotification>();
        
        return std::make_unique<UserService>(db, logger, notifier);
    }
    
    // Create custom service
    template<typename DBType, typename LoggerType, typename NotifierType, typename... Args>
    [[nodiscard]] static std::unique_ptr<UserService> createCustomService(Args&&... args) {
        auto db = std::make_shared<DBType>(std::forward<Args>(args)...);
        auto logger = std::make_shared<LoggerType>();
        auto notifier = std::make_shared<NotifierType>();
        
        return std::make_unique<UserService>(db, logger, notifier);
    }
};

// Modern application using dependency injection
class Application {
public:
    explicit Application(std::unique_ptr<UserService> userService)
        : userService_(std::move(userService)) {}
    
    void run() {
        std::cout << "=== Application Running ===" << std::endl;
        
        // Create users
        userService_->createUser("Alice", "alice@example.com");
        userService_->createUser("Bob", "bob@example.com");
        
        // Batch creation
        std::vector<std::pair<std::string, std::string>> batchUsers = {
            {"Charlie", "charlie@example.com"},
            {"Diana", "diana@example.com"}
        };
        userService_->createUsers(batchUsers);
        
        // Retrieve users
        auto user1 = userService_->getUser("user1");
        auto user2 = userService_->getUser("user2");
        
        std::cout << "Retrieved: " << user1 << ", " << user2 << std::endl;
    }

private:
    std::unique_ptr<UserService> userService_;
};

int main() {
    std::cout << "=== Optimized Dependency Inversion Principle (DIP) Example ===" << std::endl;
    
    // Bad example: Direct dependency
    std::cout << "\n--- Bad Example (Direct Dependency) ---" << std::endl;
    BadUserService badService;
    badService.createUser("John");
    std::cout << badService.getUser("user1") << std::endl;
    
    // Optimized example: Dependency injection
    std::cout << "\n--- Optimized Example (Dependency Injection) ---" << std::endl;
    
    // Create services using factory pattern
    auto mysqlService = ServiceFactory::createMySQLService();
    auto postgresService = ServiceFactory::createPostgreSQLService();
    
    // Run applications with different dependencies
    std::cout << "\n--- MySQL Application ---" << std::endl;
    Application mysqlApp(std::move(mysqlService));
    mysqlApp.run();
    
    std::cout << "\n--- PostgreSQL Application ---" << std::endl;
    Application postgresApp(std::move(postgresService));
    postgresApp.run();
    
    // Custom service creation
    auto customService = ServiceFactory::createCustomService<MySQLDatabase, FileLogger, SMSNotification>();
    Application customApp(std::move(customService));
    customApp.run();
    
    return 0;
} 