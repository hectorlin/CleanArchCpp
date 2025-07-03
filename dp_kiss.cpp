#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// KISS (Keep It Simple, Stupid) Principle
// Keep code simple and straightforward, avoid unnecessary complexity

// Bad example: Over-engineered solution
class ComplexUserManager {
private:
    struct UserData {
        std::string identifier;
        std::string personalInformation;
        std::string contactDetails;
        std::string preferences;
    };
    
    std::vector<UserData> userDatabase;
    
    class UserValidator {
    public:
        static bool validateUserIdentifier(const std::string& id) {
            return !id.empty() && id.length() >= 3;
        }
        
        static bool validatePersonalInformation(const std::string& info) {
            return !info.empty();
        }
    };
    
    class UserProcessor {
    public:
        static std::string processUserData(const UserData& data) {
            return "Processed: " + data.identifier;
        }
    };

public:
    void addUser(const std::string& name, const std::string& email) {
        UserData newUser;
        newUser.identifier = name;
        newUser.personalInformation = name;
        newUser.contactDetails = email;
        newUser.preferences = "default";
        
        if (UserValidator::validateUserIdentifier(newUser.identifier) &&
            UserValidator::validatePersonalInformation(newUser.personalInformation)) {
            userDatabase.push_back(newUser);
            std::cout << "Complex: User added successfully" << std::endl;
        }
    }
    
    void displayUsers() {
        for (const auto& user : userDatabase) {
            std::cout << "Complex: " << UserProcessor::processUserData(user) << std::endl;
        }
    }
};

// Good example: Simple and straightforward
class SimpleUserManager {
private:
    std::vector<std::string> users;

public:
    void addUser(const std::string& name) {
        if (!name.empty()) {
            users.push_back(name);
            std::cout << "Simple: Added user: " << name << std::endl;
        }
    }
    
    void displayUsers() {
        for (const auto& user : users) {
            std::cout << "Simple: User: " << user << std::endl;
        }
    }
};

// Another bad example: Overly complex algorithm
class ComplexCalculator {
public:
    double calculateAverage(const std::vector<double>& numbers) {
        if (numbers.empty()) return 0.0;
        
        double sum = 0.0;
        size_t count = 0;
        
        for (auto it = numbers.begin(); it != numbers.end(); ++it) {
            sum += *it;
            count++;
        }
        
        return sum / static_cast<double>(count);
    }
};

// Good example: Simple algorithm
class SimpleCalculator {
public:
    double calculateAverage(const std::vector<double>& numbers) {
        if (numbers.empty()) return 0.0;
        
        double sum = 0.0;
        for (double num : numbers) {
            sum += num;
        }
        
        return sum / numbers.size();
    }
};

// Bad example: Complex string processing
class ComplexStringProcessor {
public:
    std::string reverseString(const std::string& input) {
        std::string result;
        for (auto it = input.rbegin(); it != input.rend(); ++it) {
            result.push_back(*it);
        }
        return result;
    }
    
    bool isPalindrome(const std::string& input) {
        std::string processed = input;
        std::transform(processed.begin(), processed.end(), processed.begin(), ::tolower);
        processed.erase(std::remove_if(processed.begin(), processed.end(), ::isspace), processed.end());
        
        std::string reversed = reverseString(processed);
        return processed == reversed;
    }
};

// Good example: Simple string processing
class SimpleStringProcessor {
public:
    std::string reverseString(const std::string& input) {
        return std::string(input.rbegin(), input.rend());
    }
    
    bool isPalindrome(const std::string& input) {
        std::string cleaned;
        for (char c : input) {
            if (std::isalpha(c)) {
                cleaned += std::tolower(c);
            }
        }
        return cleaned == reverseString(cleaned);
    }
};

int main() {
    std::cout << "=== KISS (Keep It Simple, Stupid) Principle Example ===" << std::endl;
    
    // Complex vs Simple User Management
    std::cout << "\n--- User Management Comparison ---" << std::endl;
    
    ComplexUserManager complexManager;
    complexManager.addUser("John Doe", "john@example.com");
    complexManager.displayUsers();
    
    SimpleUserManager simpleManager;
    simpleManager.addUser("John Doe");
    simpleManager.displayUsers();
    
    // Complex vs Simple Calculator
    std::cout << "\n--- Calculator Comparison ---" << std::endl;
    
    std::vector<double> numbers = {1.0, 2.0, 3.0, 4.0, 5.0};
    
    ComplexCalculator complexCalc;
    std::cout << "Complex average: " << complexCalc.calculateAverage(numbers) << std::endl;
    
    SimpleCalculator simpleCalc;
    std::cout << "Simple average: " << simpleCalc.calculateAverage(numbers) << std::endl;
    
    // Complex vs Simple String Processing
    std::cout << "\n--- String Processing Comparison ---" << std::endl;
    
    std::string testString = "A man a plan a canal Panama";
    
    ComplexStringProcessor complexString;
    std::cout << "Complex palindrome check: " << (complexString.isPalindrome(testString) ? "Yes" : "No") << std::endl;
    
    SimpleStringProcessor simpleString;
    std::cout << "Simple palindrome check: " << (simpleString.isPalindrome(testString) ? "Yes" : "No") << std::endl;
    
    return 0;
} 