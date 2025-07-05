#include <iostream>
#include <string>
#include <vector>
#include <map>

// YAGNI (You Aren't Gonna Need It) Principle
// Don't add functionality until it's actually needed

// Bad example: Adding features that might be needed in the future
class OverEngineeredUserManager {
private:
    std::map<std::string, std::string> users;
    std::map<std::string, std::string> userRoles;
    std::map<std::string, std::vector<std::string>> userPermissions;
    std::map<std::string, std::string> userPreferences;
    std::map<std::string, std::string> userMetadata;
    bool enableLogging = false;
    bool enableCaching = false;
    bool enableEncryption = false;
    std::string databaseType = "sqlite"; // Might need MySQL later
    std::string cacheType = "memory";    // Might need Redis later

public:
    void addUser(const std::string& username, const std::string& email) {
        users[username] = email;
        userRoles[username] = "user"; // Default role
        userPermissions[username] = {"read"}; // Default permissions
        userPreferences[username] = "default"; // Default preferences
        userMetadata[username] = "created"; // Metadata
        
        if (enableLogging) {
            std::cout << "Log: User " << username << " added" << std::endl;
        }
        
        if (enableCaching) {
            std::cout << "Cache: User " << username << " cached" << std::endl;
        }
        
        if (enableEncryption) {
            std::cout << "Encrypt: User " << username << " encrypted" << std::endl;
        }
    }
    
    void setUserRole(const std::string& username, const std::string& role) {
        userRoles[username] = role;
    }
    
    void addUserPermission(const std::string& username, const std::string& permission) {
        userPermissions[username].push_back(permission);
    }
    
    void setUserPreference(const std::string& username, const std::string& preference) {
        userPreferences[username] = preference;
    }
    
    void setUserMetadata(const std::string& username, const std::string& metadata) {
        userMetadata[username] = metadata;
    }
    
    void enableFeature(const std::string& feature) {
        if (feature == "logging") enableLogging = true;
        if (feature == "caching") enableCaching = true;
        if (feature == "encryption") enableEncryption = true;
    }
    
    void setDatabaseType(const std::string& type) {
        databaseType = type;
    }
    
    void setCacheType(const std::string& type) {
        cacheType = type;
    }
    
    void displayUser(const std::string& username) {
        if (users.find(username) != users.end()) {
            std::cout << "User: " << username << " (" << users[username] << ")" << std::endl;
            std::cout << "Role: " << userRoles[username] << std::endl;
            std::cout << "Permissions: ";
            for (const auto& perm : userPermissions[username]) {
                std::cout << perm << " ";
            }
            std::cout << std::endl;
        }
    }
};

// Good example: Only implement what's needed now
class SimpleUserManager {
private:
    std::map<std::string, std::string> users; // username -> email

public:
    void addUser(const std::string& username, const std::string& email) {
        users[username] = email;
        std::cout << "Added user: " << username << " (" << email << ")" << std::endl;
    }
    
    void displayUser(const std::string& username) {
        if (users.find(username) != users.end()) {
            std::cout << "User: " << username << " (" << users[username] << ")" << std::endl;
        } else {
            std::cout << "User not found: " << username << std::endl;
        }
    }
    
    bool userExists(const std::string& username) {
        return users.find(username) != users.end();
    }
};

// Another bad example: Over-engineering a simple calculator
class FutureProofCalculator {
private:
    bool enableHistory = false;
    bool enableScientificMode = false;
    bool enableUnitConversion = false;
    std::vector<double> calculationHistory;
    std::map<std::string, double> unitConversions;

public:
    double add(double a, double b) {
        double result = a + b;
        
        if (enableHistory) {
            calculationHistory.push_back(result);
        }
        
        if (enableScientificMode) {
            std::cout << "Scientific mode: " << a << " + " << b << " = " << result << std::endl;
        }
        
        return result;
    }
    
    double multiply(double a, double b) {
        double result = a * b;
        
        if (enableHistory) {
            calculationHistory.push_back(result);
        }
        
        return result;
    }
    
    void enableFeature(const std::string& feature) {
        if (feature == "history") enableHistory = true;
        if (feature == "scientific") enableScientificMode = true;
        if (feature == "units") enableUnitConversion = true;
    }
    
    void showHistory() {
        if (enableHistory) {
            std::cout << "Calculation history: ";
            for (double result : calculationHistory) {
                std::cout << result << " ";
            }
            std::cout << std::endl;
        }
    }
};

// Good example: Simple calculator with only needed features
class SimpleCalculator {
public:
    double add(double a, double b) {
        return a + b;
    }
    
    double multiply(double a, double b) {
        return a * b;
    }
    
    double subtract(double a, double b) {
        return a - b;
    }
    
    double divide(double a, double b) {
        if (b != 0) {
            return a / b;
        }
        throw std::runtime_error("Division by zero");
    }
};

int main() {
    std::cout << "=== YAGNI (You Aren't Gonna Need It) Principle Example ===" << std::endl;
    
    // Over-engineered vs Simple User Management
    std::cout << "\n--- User Management Comparison ---" << std::endl;
    
    OverEngineeredUserManager overEngineered;
    overEngineered.addUser("john", "john@example.com");
    overEngineered.setUserRole("john", "admin");
    overEngineered.addUserPermission("john", "write");
    overEngineered.enableFeature("logging");
    overEngineered.displayUser("john");
    
    SimpleUserManager simple;
    simple.addUser("jane", "jane@example.com");
    simple.displayUser("jane");
    
    // Over-engineered vs Simple Calculator
    std::cout << "\n--- Calculator Comparison ---" << std::endl;
    
    FutureProofCalculator futureProof;
    futureProof.enableFeature("history");
    futureProof.enableFeature("scientific");
    std::cout << "Future-proof result: " << futureProof.add(5, 3) << std::endl;
    futureProof.showHistory();
    
    SimpleCalculator simpleCalc;
    std::cout << "Simple result: " << simpleCalc.add(5, 3) << std::endl;
    std::cout << "Simple multiply: " << simpleCalc.multiply(4, 6) << std::endl;
    
    return 0;
} 