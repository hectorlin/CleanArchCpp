#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// DRY (Don't Repeat Yourself) Principle
// Avoid code duplication by extracting common functionality

// Bad example: Code duplication
class BadUserValidator {
public:
    bool validateEmail(const std::string& email) {
        if (email.empty()) return false;
        if (email.find('@') == std::string::npos) return false;
        if (email.find('.') == std::string::npos) return false;
        return true;
    }
    
    bool validatePhone(const std::string& phone) {
        if (phone.empty()) return false;
        if (phone.length() < 10) return false;
        for (char c : phone) {
            if (!std::isdigit(c)) return false;
        }
        return true;
    }
    
    bool validateName(const std::string& name) {
        if (name.empty()) return false;
        if (name.length() < 2) return false;
        for (char c : name) {
            if (!std::isalpha(c) && c != ' ') return false;
        }
        return true;
    }
};

// Good example: DRY principle applied
class StringValidator {
public:
    static bool isEmpty(const std::string& str) {
        return str.empty();
    }
    
    static bool hasMinLength(const std::string& str, size_t minLength) {
        return str.length() >= minLength;
    }
    
    static bool containsOnly(const std::string& str, const std::string& allowedChars) {
        return str.find_first_not_of(allowedChars) == std::string::npos;
    }
    
    static bool contains(const std::string& str, char ch) {
        return str.find(ch) != std::string::npos;
    }
};

class GoodUserValidator {
public:
    bool validateEmail(const std::string& email) {
        if (StringValidator::isEmpty(email)) return false;
        if (!StringValidator::contains(email, '@')) return false;
        if (!StringValidator::contains(email, '.')) return false;
        return true;
    }
    
    bool validatePhone(const std::string& phone) {
        if (StringValidator::isEmpty(phone)) return false;
        if (!StringValidator::hasMinLength(phone, 10)) return false;
        if (!StringValidator::containsOnly(phone, "0123456789")) return false;
        return true;
    }
    
    bool validateName(const std::string& name) {
        if (StringValidator::isEmpty(name)) return false;
        if (!StringValidator::hasMinLength(name, 2)) return false;
        if (!StringValidator::containsOnly(name, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ")) return false;
        return true;
    }
};

// Template-based approach for even more DRY code
template<typename ValidatorFunc>
class ValidationRule {
public:
    ValidationRule(ValidatorFunc func) : validator(func) {}
    
    bool validate(const std::string& value) const {
        return validator(value);
    }
    
private:
    ValidatorFunc validator;
};

class AdvancedUserValidator {
public:
    bool validateEmail(const std::string& email) {
        std::vector<ValidationRule<std::function<bool(const std::string&)>>> rules = {
            ValidationRule([](const std::string& s) { return !StringValidator::isEmpty(s); }),
            ValidationRule([](const std::string& s) { return StringValidator::contains(s, '@'); }),
            ValidationRule([](const std::string& s) { return StringValidator::contains(s, '.'); })
        };
        
        return std::all_of(rules.begin(), rules.end(), 
                          [&email](const auto& rule) { return rule.validate(email); });
    }
    
    bool validatePhone(const std::string& phone) {
        std::vector<ValidationRule<std::function<bool(const std::string&)>>> rules = {
            ValidationRule([](const std::string& s) { return !StringValidator::isEmpty(s); }),
            ValidationRule([](const std::string& s) { return StringValidator::hasMinLength(s, 10); }),
            ValidationRule([](const std::string& s) { return StringValidator::containsOnly(s, "0123456789"); })
        };
        
        return std::all_of(rules.begin(), rules.end(), 
                          [&phone](const auto& rule) { return rule.validate(phone); });
    }
};

int main() {
    std::cout << "=== DRY (Don't Repeat Yourself) Principle Example ===" << std::endl;
    
    // Bad example: Code duplication
    std::cout << "\n--- Bad Example (Code Duplication) ---" << std::endl;
    BadUserValidator badValidator;
    std::cout << "Email validation: " << (badValidator.validateEmail("test@example.com") ? "Valid" : "Invalid") << std::endl;
    std::cout << "Phone validation: " << (badValidator.validatePhone("1234567890") ? "Valid" : "Invalid") << std::endl;
    std::cout << "Name validation: " << (badValidator.validateName("John Doe") ? "Valid" : "Invalid") << std::endl;
    
    // Good example: DRY applied
    std::cout << "\n--- Good Example (DRY Applied) ---" << std::endl;
    GoodUserValidator goodValidator;
    std::cout << "Email validation: " << (goodValidator.validateEmail("test@example.com") ? "Valid" : "Invalid") << std::endl;
    std::cout << "Phone validation: " << (goodValidator.validatePhone("1234567890") ? "Valid" : "Invalid") << std::endl;
    std::cout << "Name validation: " << (goodValidator.validateName("John Doe") ? "Valid" : "Invalid") << std::endl;
    
    // Advanced example: Template-based validation
    std::cout << "\n--- Advanced Example (Template-based) ---" << std::endl;
    AdvancedUserValidator advancedValidator;
    std::cout << "Email validation: " << (advancedValidator.validateEmail("test@example.com") ? "Valid" : "Invalid") << std::endl;
    std::cout << "Phone validation: " << (advancedValidator.validatePhone("1234567890") ? "Valid" : "Invalid") << std::endl;
    
    return 0;
} 