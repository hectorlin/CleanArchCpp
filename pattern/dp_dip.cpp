#include <iostream>
#include <string>
#include <memory>

// Dependency Inversion Principle (DIP)
// High-level modules should not depend on low-level modules. Both should depend on abstractions.

// Bad example: High-level module depends on low-level module
class BadMySQLDatabase {
public:
    void save(const std::string& data) {
        std::cout << "Saving to MySQL: " << data << std::endl;
    }
};

class BadUserService {
private:
    BadMySQLDatabase database; // Direct dependency on concrete class

public:
    void createUser(const std::string& name) {
        database.save("User: " + name);
    }
};

// Good example: Both depend on abstraction
class DatabaseInterface {
public:
    virtual ~DatabaseInterface() = default;
    virtual void save(const std::string& data) = 0;
};

class MySQLDatabase : public DatabaseInterface {
public:
    void save(const std::string& data) override {
        std::cout << "Saving to MySQL: " << data << std::endl;
    }
};

class PostgreSQLDatabase : public DatabaseInterface {
public:
    void save(const std::string& data) override {
        std::cout << "Saving to PostgreSQL: " << data << std::endl;
    }
};

class FileDatabase : public DatabaseInterface {
public:
    void save(const std::string& data) override {
        std::cout << "Saving to file: " << data << std::endl;
    }
};

class GoodUserService {
private:
    std::shared_ptr<DatabaseInterface> database; // Depends on abstraction

public:
    GoodUserService(std::shared_ptr<DatabaseInterface> db) : database(db) {}
    
    void createUser(const std::string& name) {
        database->save("User: " + name);
    }
};

// Factory for creating database instances
class DatabaseFactory {
public:
    static std::shared_ptr<DatabaseInterface> createDatabase(const std::string& type) {
        if (type == "mysql") {
            return std::make_shared<MySQLDatabase>();
        } else if (type == "postgresql") {
            return std::make_shared<PostgreSQLDatabase>();
        } else if (type == "file") {
            return std::make_shared<FileDatabase>();
        }
        throw std::runtime_error("Unknown database type: " + type);
    }
};

int main() {
    std::cout << "=== Dependency Inversion Principle (DIP) Example ===" << std::endl;
    
    // Bad example: Tight coupling
    std::cout << "\n--- Bad Example (Tight Coupling) ---" << std::endl;
    BadUserService badService;
    badService.createUser("John Doe");
    
    // Good example: Dependency injection
    std::cout << "\n--- Good Example (Dependency Injection) ---" << std::endl;
    
    // Using MySQL
    auto mysqlDb = DatabaseFactory::createDatabase("mysql");
    GoodUserService mysqlService(mysqlDb);
    mysqlService.createUser("Jane Smith");
    
    // Using PostgreSQL
    auto postgresDb = DatabaseFactory::createDatabase("postgresql");
    GoodUserService postgresService(postgresDb);
    postgresService.createUser("Bob Johnson");
    
    // Using File
    auto fileDb = DatabaseFactory::createDatabase("file");
    GoodUserService fileService(fileDb);
    fileService.createUser("Alice Brown");
    
    return 0;
} 