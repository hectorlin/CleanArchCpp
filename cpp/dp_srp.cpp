#include <iostream>
#include <string>
#include <vector>

// Single Responsibility Principle (SRP)
// A class should have only one reason to change

// Bad example: Class with multiple responsibilities
class BadUserManager {
public:
    void addUser(const std::string& name, const std::string& email) {
        // User management responsibility
        users.push_back({name, email});
        std::cout << "User added: " << name << std::endl;
    }
    
    void sendEmail(const std::string& email, const std::string& message) {
        // Email sending responsibility
        std::cout << "Sending email to " << email << ": " << message << std::endl;
    }
    
    void saveToDatabase() {
        // Database responsibility
        std::cout << "Saving users to database..." << std::endl;
    }
    
    void generateReport() {
        // Reporting responsibility
        std::cout << "Generating user report..." << std::endl;
    }

private:
    struct User {
        std::string name;
        std::string email;
    };
    std::vector<User> users;
};

// Good example: Separate classes with single responsibilities
class User {
public:
    User(const std::string& name, const std::string& email) 
        : name(name), email(email) {}
    
    std::string getName() const { return name; }
    std::string getEmail() const { return email; }

private:
    std::string name;
    std::string email;
};

class UserRepository {
public:
    void addUser(const User& user) {
        users.push_back(user);
        std::cout << "User added: " << user.getName() << std::endl;
    }
    
    void saveToDatabase() {
        std::cout << "Saving users to database..." << std::endl;
    }
    
    std::vector<User> getAllUsers() const {
        return users;
    }

private:
    std::vector<User> users;
};

class EmailService {
public:
    void sendEmail(const std::string& email, const std::string& message) {
        std::cout << "Sending email to " << email << ": " << message << std::endl;
    }
};

class ReportGenerator {
public:
    void generateUserReport(const std::vector<User>& users) {
        std::cout << "Generating user report for " << users.size() << " users..." << std::endl;
        for (const auto& user : users) {
            std::cout << "- " << user.getName() << " (" << user.getEmail() << ")" << std::endl;
        }
    }
};

int main() {
    std::cout << "=== Single Responsibility Principle (SRP) Example ===" << std::endl;
    
    // Bad example
    std::cout << "\n--- Bad Example (Multiple Responsibilities) ---" << std::endl;
    BadUserManager badManager;
    badManager.addUser("John Doe", "john@example.com");
    badManager.sendEmail("john@example.com", "Welcome!");
    badManager.saveToDatabase();
    badManager.generateReport();
    
    // Good example
    std::cout << "\n--- Good Example (Single Responsibility) ---" << std::endl;
    UserRepository userRepo;
    EmailService emailService;
    ReportGenerator reportGen;
    
    User user1("Jane Smith", "jane@example.com");
    User user2("Bob Johnson", "bob@example.com");
    
    userRepo.addUser(user1);
    userRepo.addUser(user2);
    
    emailService.sendEmail(user1.getEmail(), "Welcome to our system!");
    emailService.sendEmail(user2.getEmail(), "Welcome to our system!");
    
    userRepo.saveToDatabase();
    reportGen.generateUserReport(userRepo.getAllUsers());
    
    return 0;
} 