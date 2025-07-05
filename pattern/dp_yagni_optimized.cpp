#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <functional>
#include <type_traits>
#include <map>

// Optimized YAGNI (You Aren't Gonna Need It) Principle Example
// Using modern C++17/20 features for better performance and maintainability

// Bad example: Implementing features you don't need yet
class OverEngineeredUserManager {
public:
    // Unnecessary complexity for current requirements
    enum class UserStatus { ACTIVE, INACTIVE, SUSPENDED, DELETED, PENDING_VERIFICATION };
    enum class UserRole { ADMIN, MODERATOR, USER, GUEST, PREMIUM, VIP };
    enum class AccountType { FREE, BASIC, PREMIUM, ENTERPRISE, CUSTOM };
    
    struct UserPreferences {
        bool emailNotifications = true;
        bool smsNotifications = false;
        bool pushNotifications = true;
        std::string timezone = "UTC";
        std::string language = "en";
        bool darkMode = false;
        int itemsPerPage = 20;
    };
    
    struct UserMetadata {
        std::string ipAddress;
        std::string userAgent;
        std::string lastLoginTime;
        int loginCount = 0;
        std::string registrationSource;
        bool emailVerified = false;
        bool phoneVerified = false;
    };
    
    class User {
    public:
        User(std::string name, std::string email) 
            : name_(std::move(name)), email_(std::move(email)) {}
        
        // Getters and setters for all properties
        const std::string& getName() const { return name_; }
        void setName(const std::string& name) { name_ = name; }
        
        const std::string& getEmail() const { return email_; }
        void setEmail(const std::string& email) { email_ = email; }
        
        UserStatus getStatus() const { return status_; }
        void setStatus(UserStatus status) { status_ = status; }
        
        UserRole getRole() const { return role_; }
        void setRole(UserRole role) { role_ = role; }
        
        AccountType getAccountType() const { return accountType_; }
        void setAccountType(AccountType type) { accountType_ = type; }
        
        const UserPreferences& getPreferences() const { return preferences_; }
        void setPreferences(const UserPreferences& prefs) { preferences_ = prefs; }
        
        const UserMetadata& getMetadata() const { return metadata_; }
        void setMetadata(const UserMetadata& meta) { metadata_ = meta; }
        
        // Complex methods that aren't needed yet
        void sendWelcomeEmail() {
            std::cout << "Sending welcome email to " << email_ << std::endl;
        }
        
        void sendPasswordResetEmail() {
            std::cout << "Sending password reset email to " << email_ << std::endl;
        }
        
        void updateLastLoginTime() {
            std::cout << "Updating last login time for " << name_ << std::endl;
        }
        
        bool hasPermission(const std::string& permission) {
            std::cout << "Checking permission " << permission << " for " << name_ << std::endl;
            return role_ == UserRole::ADMIN;
        }
        
        void upgradeAccount(AccountType newType) {
            std::cout << "Upgrading account for " << name_ << " to " << static_cast<int>(newType) << std::endl;
            accountType_ = newType;
        }

    private:
        std::string name_;
        std::string email_;
        UserStatus status_ = UserStatus::ACTIVE;
        UserRole role_ = UserRole::USER;
        AccountType accountType_ = AccountType::FREE;
        UserPreferences preferences_;
        UserMetadata metadata_;
    };
    
    void addUser(std::unique_ptr<User> user) {
        users_.push_back(std::move(user));
        std::cout << "User added with full feature set" << std::endl;
    }
    
    void removeUser(const std::string& email) {
        users_.erase(
            std::remove_if(users_.begin(), users_.end(),
                [&email](const auto& user) { return user->getEmail() == email; }),
            users_.end()
        );
        std::cout << "User removed with full cleanup" << std::endl;
    }

private:
    std::vector<std::unique_ptr<User>> users_;
};

// Optimized example: Only implement what you need now
// Using modern C++ features for better performance and simplicity

// Simple user class with only current requirements
class SimpleUser {
public:
    SimpleUser(std::string name, std::string email) 
        : name_(std::move(name)), email_(std::move(email)) {}
    
    // Only the methods we actually need
    [[nodiscard]] const std::string& getName() const noexcept { return name_; }
    [[nodiscard]] const std::string& getEmail() const noexcept { return email_; }
    
    // Simple validation
    [[nodiscard]] bool isValid() const noexcept {
        return !name_.empty() && !email_.empty() && email_.find('@') != std::string::npos;
    }

private:
    std::string name_;
    std::string email_;
};

// Simple user manager with only current requirements
class SimpleUserManager {
public:
    void addUser(std::unique_ptr<SimpleUser> user) {
        if (user && user->isValid()) {
            users_.push_back(std::move(user));
            std::cout << "User added: " << users_.back()->getName() << std::endl;
        }
    }
    
    void removeUser(const std::string& email) {
        auto it = std::find_if(users_.begin(), users_.end(),
            [&email](const auto& user) { return user->getEmail() == email; });
        
        if (it != users_.end()) {
            std::cout << "User removed: " << (*it)->getName() << std::endl;
            users_.erase(it);
        }
    }
    
    [[nodiscard]] const SimpleUser* findUser(const std::string& email) const {
        auto it = std::find_if(users_.begin(), users_.end(),
            [&email](const auto& user) { return user->getEmail() == email; });
        return it != users_.end() ? it->get() : nullptr;
    }
    
    [[nodiscard]] size_t getUserCount() const noexcept {
        return users_.size();
    }
    
    // Simple iteration
    template<typename Func>
    void forEachUser(Func func) const {
        std::for_each(users_.begin(), users_.end(),
            [&func](const auto& user) { func(*user); });
    }

private:
    std::vector<std::unique_ptr<SimpleUser>> users_;
};

// Simple data storage with only current requirements
class SimpleDataStore {
public:
    // Only store what we need now
    void save(const std::string& key, const std::string& value) {
        data_[key] = value;
        std::cout << "Saved: " << key << " = " << value << std::endl;
    }
    
    [[nodiscard]] std::string load(const std::string& key) const {
        auto it = data_.find(key);
        return it != data_.end() ? it->second : "";
    }
    
    void remove(const std::string& key) {
        if (data_.erase(key) > 0) {
            std::cout << "Removed: " << key << std::endl;
        }
    }
    
    [[nodiscard]] bool exists(const std::string& key) const {
        return data_.find(key) != data_.end();
    }

private:
    std::map<std::string, std::string> data_;
};

// Simple logger with only current requirements
class SimpleLogger {
public:
    void log(const std::string& message) {
        std::cout << "[LOG] " << message << std::endl;
    }
    
    void error(const std::string& message) {
        std::cerr << "[ERROR] " << message << std::endl;
    }
};

// Simple application with only current requirements
class SimpleApplication {
public:
    SimpleApplication() = default;
    
    void run() {
        logger_.log("Application started");
        
        // Add some users
        userManager_.addUser(std::make_unique<SimpleUser>("Alice", "alice@example.com"));
        userManager_.addUser(std::make_unique<SimpleUser>("Bob", "bob@example.com"));
        
        // Store some data
        dataStore_.save("config", "simple");
        dataStore_.save("version", "1.0");
        
        // Find a user
        if (const auto* user = userManager_.findUser("alice@example.com")) {
            logger_.log("Found user: " + user->getName());
        }
        
        // Display user count
        logger_.log("Total users: " + std::to_string(userManager_.getUserCount()));
        
        // List all users
        userManager_.forEachUser([this](const SimpleUser& user) {
            logger_.log("User: " + user.getName() + " (" + user.getEmail() + ")");
        });
        
        logger_.log("Application completed");
    }

private:
    SimpleUserManager userManager_;
    SimpleDataStore dataStore_;
    SimpleLogger logger_;
};

// Future extension example (only when needed)
class ExtendedUser : public SimpleUser {
public:
    ExtendedUser(std::string name, std::string email, std::string role)
        : SimpleUser(std::move(name), std::move(email)), role_(std::move(role)) {}
    
    [[nodiscard]] const std::string& getRole() const noexcept { return role_; }
    
    // Only add this when you actually need it
    [[nodiscard]] bool isAdmin() const noexcept {
        return role_ == "admin";
    }

private:
    std::string role_;
};

// Template-based extension (only when needed)
template<typename UserType = SimpleUser>
class ExtensibleUserManager {
public:
    void addUser(std::unique_ptr<UserType> user) {
        if (user && user->isValid()) {
            users_.push_back(std::move(user));
        }
    }
    
    template<typename Func>
    void forEachUser(Func func) const {
        std::for_each(users_.begin(), users_.end(),
            [&func](const auto& user) { func(*user); });
    }

private:
    std::vector<std::unique_ptr<UserType>> users_;
};

int main() {
    std::cout << "=== Optimized YAGNI (You Aren't Gonna Need It) Principle Example ===" << std::endl;
    
    // Bad example: Over-engineered solution
    std::cout << "\n--- Bad Example (Over-engineered) ---" << std::endl;
    OverEngineeredUserManager badManager;
    
    auto badUser = std::make_unique<OverEngineeredUserManager::User>("John", "john@example.com");
    badUser->setRole(OverEngineeredUserManager::UserRole::ADMIN);
    badUser->setAccountType(OverEngineeredUserManager::AccountType::PREMIUM);
    
    badManager.addUser(std::move(badUser));
    badManager.removeUser("john@example.com");
    
    // Optimized example: Only what you need
    std::cout << "\n--- Optimized Example (YAGNI Applied) ---" << std::endl;
    
    SimpleApplication app;
    app.run();
    
    // Demonstrate future extension (only when needed)
    std::cout << "\n--- Future Extension (When Needed) ---" << std::endl;
    
    ExtensibleUserManager<ExtendedUser> extendedManager;
    extendedManager.addUser(std::make_unique<ExtendedUser>("Admin", "admin@example.com", "admin"));
    extendedManager.addUser(std::make_unique<ExtendedUser>("User", "user@example.com", "user"));
    
    extendedManager.forEachUser([](const ExtendedUser& user) {
        std::cout << "Extended User: " << user.getName() 
                  << " (" << user.getRole() << ")"
                  << (user.isAdmin() ? " [ADMIN]" : "") << std::endl;
    });
    
    return 0;
} 