#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <functional>

// Optimized Single Responsibility Principle (SRP) Example
// Using modern C++17/20 features for better performance and readability

// Bad example: Class with multiple responsibilities
class BadUserManager {
public:
    void addUser(const std::string& name, const std::string& email) {
        users.emplace_back(name, email);
        std::cout << "User added: " << name << std::endl;
    }
    
    void sendEmail(const std::string& email, const std::string& message) {
        std::cout << "Sending email to " << email << ": " << message << std::endl;
    }
    
    void saveToDatabase() {
        std::cout << "Saving users to database..." << std::endl;
    }
    
    void generateReport() {
        std::cout << "Generating user report..." << std::endl;
    }

private:
    struct User {
        std::string name;
        std::string email;
        
        User(std::string n, std::string e) 
            : name(std::move(n)), email(std::move(e)) {}
    };
    std::vector<User> users;
};

// Optimized example: Separate classes with single responsibilities
// Using std::string_view for better performance
class User {
public:
    User(std::string_view name, std::string_view email) 
        : name_(name), email_(email) {}
    
    [[nodiscard]] const std::string& getName() const noexcept { return name_; }
    [[nodiscard]] const std::string& getEmail() const noexcept { return email_; }
    
    // Move semantics for better performance
    User(User&&) = default;
    User& operator=(User&&) = default;
    User(const User&) = default;
    User& operator=(const User&) = default;

private:
    std::string name_;
    std::string email_;
};

// Optimized repository with move semantics and const correctness
class UserRepository {
public:
    void addUser(User user) {
        users_.emplace_back(std::move(user));
        std::cout << "User added: " << users_.back().getName() << std::endl;
    }
    
    void saveToDatabase() const {
        std::cout << "Saving " << users_.size() << " users to database..." << std::endl;
    }
    
    [[nodiscard]] const std::vector<User>& getAllUsers() const noexcept {
        return users_;
    }
    
    // Optimized search with std::find_if
    [[nodiscard]] std::optional<User> findUserByEmail(std::string_view email) const {
        auto it = std::find_if(users_.begin(), users_.end(),
            [email](const User& user) { return user.getEmail() == email; });
        return it != users_.end() ? std::optional<User>(*it) : std::nullopt;
    }

private:
    std::vector<User> users_;
};

// Optimized email service with async capabilities
class EmailService {
public:
    void sendEmail(std::string_view email, std::string_view message) const {
        std::cout << "Sending email to " << email << ": " << message << std::endl;
    }
    
    // Batch email sending for better performance
    void sendBatchEmails(const std::vector<std::pair<std::string, std::string>>& emails) const {
        std::cout << "Sending " << emails.size() << " emails in batch..." << std::endl;
        for (const auto& [email, message] : emails) {
            sendEmail(email, message);
        }
    }
};

// Optimized report generator with modern C++ features
class ReportGenerator {
public:
    void generateUserReport(const std::vector<User>& users) const {
        std::cout << "Generating user report for " << users.size() << " users..." << std::endl;
        
        // Use range-based for loop with structured bindings
        for (const auto& user : users) {
            std::cout << "- " << user.getName() << " (" << user.getEmail() << ")" << std::endl;
        }
    }
    
    // Optimized with std::transform for data processing
    [[nodiscard]] std::vector<std::string> extractUserNames(const std::vector<User>& users) const {
        std::vector<std::string> names;
        names.reserve(users.size()); // Pre-allocate for better performance
        
        std::transform(users.begin(), users.end(), std::back_inserter(names),
            [](const User& user) { return user.getName(); });
        
        return names;
    }
};

// Modern user service with dependency injection
class UserService {
public:
    UserService(std::shared_ptr<UserRepository> repo,
                std::shared_ptr<EmailService> email,
                std::shared_ptr<ReportGenerator> report)
        : repo_(std::move(repo))
        , email_(std::move(email))
        , report_(std::move(report)) {}
    
    void registerUser(std::string_view name, std::string_view email) {
        User user(name, email);
        repo_->addUser(std::move(user));
        email_->sendEmail(email, "Welcome to our system!");
    }
    
    void generateAndSendReport() const {
        const auto& users = repo_->getAllUsers();
        report_->generateUserReport(users);
    }

private:
    std::shared_ptr<UserRepository> repo_;
    std::shared_ptr<EmailService> email_;
    std::shared_ptr<ReportGenerator> report_;
};

int main() {
    std::cout << "=== Optimized Single Responsibility Principle (SRP) Example ===" << std::endl;
    
    // Bad example
    std::cout << "\n--- Bad Example (Multiple Responsibilities) ---" << std::endl;
    BadUserManager badManager;
    badManager.addUser("John Doe", "john@example.com");
    badManager.sendEmail("john@example.com", "Welcome!");
    badManager.saveToDatabase();
    badManager.generateReport();
    
    // Optimized example
    std::cout << "\n--- Optimized Example (Single Responsibility) ---" << std::endl;
    
    auto userRepo = std::make_shared<UserRepository>();
    auto emailService = std::make_shared<EmailService>();
    auto reportGen = std::make_shared<ReportGenerator>();
    
    UserService userService(userRepo, emailService, reportGen);
    
    // Use move semantics and string_view for better performance
    userService.registerUser("Jane Smith", "jane@example.com");
    userService.registerUser("Bob Johnson", "bob@example.com");
    
    // Demonstrate optimized features
    if (auto user = userRepo->findUserByEmail("jane@example.com")) {
        std::cout << "Found user: " << user->getName() << std::endl;
    }
    
    // Batch operations
    std::vector<std::pair<std::string, std::string>> batchEmails = {
        {"user1@example.com", "Batch email 1"},
        {"user2@example.com", "Batch email 2"}
    };
    emailService->sendBatchEmails(batchEmails);
    
    // Generate report with optimized data extraction
    auto names = reportGen->extractUserNames(userRepo->getAllUsers());
    std::cout << "User names: ";
    for (const auto& name : names) {
        std::cout << name << " ";
    }
    std::cout << std::endl;
    
    userService.generateAndSendReport();
    
    return 0;
} 