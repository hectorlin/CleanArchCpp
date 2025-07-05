#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <type_traits>
#include <regex>

// Optimized DRY (Don't Repeat Yourself) Principle Example
// Using modern C++17/20 features for better performance and maintainability

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

// Optimized example: DRY principle applied with modern C++ features
// Using std::string_view for better performance and const correctness

// Modern string utilities with std::string_view
class StringUtils {
public:
    [[nodiscard]] static bool isEmpty(std::string_view str) noexcept {
        return str.empty();
    }
    
    [[nodiscard]] static bool hasMinLength(std::string_view str, size_t minLength) noexcept {
        return str.length() >= minLength;
    }
    
    [[nodiscard]] static bool hasMaxLength(std::string_view str, size_t maxLength) noexcept {
        return str.length() <= maxLength;
    }
    
    [[nodiscard]] static bool containsOnly(std::string_view str, std::string_view allowedChars) noexcept {
        return str.find_first_not_of(allowedChars) == std::string_view::npos;
    }
    
    [[nodiscard]] static bool contains(std::string_view str, char ch) noexcept {
        return str.find(ch) != std::string_view::npos;
    }
    
    [[nodiscard]] static bool startsWith(std::string_view str, std::string_view prefix) noexcept {
        return str.substr(0, prefix.length()) == prefix;
    }
    
    [[nodiscard]] static bool endsWith(std::string_view str, std::string_view suffix) noexcept {
        if (str.length() < suffix.length()) return false;
        return str.substr(str.length() - suffix.length()) == suffix;
    }
    
    [[nodiscard]] static std::string toLower(std::string_view str) {
        std::string result;
        result.reserve(str.length());
        std::transform(str.begin(), str.end(), std::back_inserter(result), ::tolower);
        return result;
    }
    
    [[nodiscard]] static std::string toUpper(std::string_view str) {
        std::string result;
        result.reserve(str.length());
        std::transform(str.begin(), str.end(), std::back_inserter(result), ::toupper);
        return result;
    }
};

// Modern validation framework using std::function and templates
template<typename T>
class ValidationRule {
public:
    using ValidatorFunc = std::function<bool(const T&)>;
    
    explicit ValidationRule(ValidatorFunc func, std::string errorMessage = "")
        : validator_(std::move(func)), errorMessage_(std::move(errorMessage)) {}
    
    [[nodiscard]] bool validate(const T& value) const {
        return validator_(value);
    }
    
    [[nodiscard]] const std::string& getErrorMessage() const noexcept {
        return errorMessage_;
    }

private:
    ValidatorFunc validator_;
    std::string errorMessage_;
};

// Modern validator using composition and templates
template<typename T>
class Validator {
public:
    void addRule(ValidationRule<T> rule) {
        rules_.push_back(std::move(rule));
    }
    
    [[nodiscard]] bool validate(const T& value) const {
        return std::all_of(rules_.begin(), rules_.end(),
            [&value](const auto& rule) { return rule.validate(value); });
    }
    
    [[nodiscard]] std::vector<std::string> getErrors(const T& value) const {
        std::vector<std::string> errors;
        for (const auto& rule : rules_) {
            if (!rule.validate(value)) {
                errors.push_back(rule.getErrorMessage());
            }
        }
        return errors;
    }
    
    // Batch validation with modern C++ features
    [[nodiscard]] std::vector<bool> validateBatch(const std::vector<T>& values) const {
        std::vector<bool> results;
        results.reserve(values.size());
        std::transform(values.begin(), values.end(), std::back_inserter(results),
            [this](const T& value) { return validate(value); });
        return results;
    }

private:
    std::vector<ValidationRule<T>> rules_;
};

// Modern user validator using the DRY principle
class ModernUserValidator {
public:
    ModernUserValidator() {
        setupEmailValidator();
        setupPhoneValidator();
        setupNameValidator();
        setupPasswordValidator();
    }
    
    [[nodiscard]] bool validateEmail(std::string_view email) const {
        return emailValidator_.validate(std::string(email));
    }
    
    [[nodiscard]] bool validatePhone(std::string_view phone) const {
        return phoneValidator_.validate(std::string(phone));
    }
    
    [[nodiscard]] bool validateName(std::string_view name) const {
        return nameValidator_.validate(std::string(name));
    }
    
    [[nodiscard]] bool validatePassword(std::string_view password) const {
        return passwordValidator_.validate(std::string(password));
    }
    
    // Comprehensive validation with error reporting
    [[nodiscard]] std::vector<std::string> validateUser(const std::string& email, 
                                                       const std::string& phone,
                                                       const std::string& name,
                                                       const std::string& password) const {
        std::vector<std::string> errors;
        
        auto emailErrors = emailValidator_.getErrors(email);
        auto phoneErrors = phoneValidator_.getErrors(phone);
        auto nameErrors = nameValidator_.getErrors(name);
        auto passwordErrors = passwordValidator_.getErrors(password);
        
        errors.insert(errors.end(), emailErrors.begin(), emailErrors.end());
        errors.insert(errors.end(), phoneErrors.begin(), phoneErrors.end());
        errors.insert(errors.end(), nameErrors.begin(), nameErrors.end());
        errors.insert(errors.end(), passwordErrors.begin(), passwordErrors.end());
        
        return errors;
    }
    
    // Batch validation for multiple users
    [[nodiscard]] std::vector<bool> validateEmails(const std::vector<std::string>& emails) const {
        return emailValidator_.validateBatch(emails);
    }

private:
    void setupEmailValidator() {
        emailValidator_.addRule(ValidationRule<std::string>(
            [](const std::string& email) { return !StringUtils::isEmpty(email); },
            "Email cannot be empty"));
        
        emailValidator_.addRule(ValidationRule<std::string>(
            [](const std::string& email) { return StringUtils::contains(email, '@'); },
            "Email must contain @"));
        
        emailValidator_.addRule(ValidationRule<std::string>(
            [](const std::string& email) { return StringUtils::contains(email, '.'); },
            "Email must contain domain"));
        
        emailValidator_.addRule(ValidationRule<std::string>(
            [](const std::string& email) { return StringUtils::hasMinLength(email, 5); },
            "Email must be at least 5 characters"));
    }
    
    void setupPhoneValidator() {
        phoneValidator_.addRule(ValidationRule<std::string>(
            [](const std::string& phone) { return !StringUtils::isEmpty(phone); },
            "Phone cannot be empty"));
        
        phoneValidator_.addRule(ValidationRule<std::string>(
            [](const std::string& phone) { return StringUtils::hasMinLength(phone, 10); },
            "Phone must be at least 10 digits"));
        
        phoneValidator_.addRule(ValidationRule<std::string>(
            [](const std::string& phone) { return StringUtils::containsOnly(phone, "0123456789"); },
            "Phone must contain only digits"));
    }
    
    void setupNameValidator() {
        nameValidator_.addRule(ValidationRule<std::string>(
            [](const std::string& name) { return !StringUtils::isEmpty(name); },
            "Name cannot be empty"));
        
        nameValidator_.addRule(ValidationRule<std::string>(
            [](const std::string& name) { return StringUtils::hasMinLength(name, 2); },
            "Name must be at least 2 characters"));
        
        nameValidator_.addRule(ValidationRule<std::string>(
            [](const std::string& name) { 
                return StringUtils::containsOnly(name, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ "); 
            },
            "Name must contain only letters and spaces"));
    }
    
    void setupPasswordValidator() {
        passwordValidator_.addRule(ValidationRule<std::string>(
            [](const std::string& password) { return !StringUtils::isEmpty(password); },
            "Password cannot be empty"));
        
        passwordValidator_.addRule(ValidationRule<std::string>(
            [](const std::string& password) { return StringUtils::hasMinLength(password, 8); },
            "Password must be at least 8 characters"));
        
        passwordValidator_.addRule(ValidationRule<std::string>(
            [](const std::string& password) { 
                return StringUtils::contains(password, std::toupper(password[0])) ||
                       std::any_of(password.begin(), password.end(), ::isupper);
            },
            "Password must contain at least one uppercase letter"));
        
        passwordValidator_.addRule(ValidationRule<std::string>(
            [](const std::string& password) { 
                return std::any_of(password.begin(), password.end(), ::isdigit);
            },
            "Password must contain at least one digit"));
    }

private:
    Validator<std::string> emailValidator_;
    Validator<std::string> phoneValidator_;
    Validator<std::string> nameValidator_;
    Validator<std::string> passwordValidator_;
};

// Modern data processor using DRY principle
class DataProcessor {
public:
    // Generic data processing with std::function
    template<typename T>
    using ProcessorFunc = std::function<T(const T&)>;
    
    template<typename T>
    [[nodiscard]] std::vector<T> processBatch(const std::vector<T>& data, ProcessorFunc<T> processor) {
        std::vector<T> results;
        results.reserve(data.size());
        std::transform(data.begin(), data.end(), std::back_inserter(results), processor);
        return results;
    }
    
    // Generic filtering
    template<typename T>
    using FilterFunc = std::function<bool(const T&)>;
    
    template<typename T>
    [[nodiscard]] std::vector<T> filter(const std::vector<T>& data, FilterFunc<T> filter) {
        std::vector<T> results;
        std::copy_if(data.begin(), data.end(), std::back_inserter(results), filter);
        return results;
    }
    
    // Generic sorting with custom comparator
    template<typename T>
    using CompareFunc = std::function<bool(const T&, const T&)>;
    
    template<typename T>
    void sort(std::vector<T>& data, CompareFunc<T> comparator) {
        std::sort(data.begin(), data.end(), comparator);
    }
};

int main() {
    std::cout << "=== Optimized DRY (Don't Repeat Yourself) Principle Example ===" << std::endl;
    
    // Bad example: Code duplication
    std::cout << "\n--- Bad Example (Code Duplication) ---" << std::endl;
    BadUserValidator badValidator;
    std::cout << "Email validation: " << (badValidator.validateEmail("test@example.com") ? "Valid" : "Invalid") << std::endl;
    std::cout << "Phone validation: " << (badValidator.validatePhone("1234567890") ? "Valid" : "Invalid") << std::endl;
    std::cout << "Name validation: " << (badValidator.validateName("John Doe") ? "Valid" : "Invalid") << std::endl;
    
    // Optimized example: DRY applied with modern C++ features
    std::cout << "\n--- Optimized Example (DRY Applied) ---" << std::endl;
    
    ModernUserValidator validator;
    
    // Individual validations
    std::cout << "Email validation: " << (validator.validateEmail("test@example.com") ? "Valid" : "Invalid") << std::endl;
    std::cout << "Phone validation: " << (validator.validatePhone("1234567890") ? "Valid" : "Invalid") << std::endl;
    std::cout << "Name validation: " << (validator.validateName("John Doe") ? "Valid" : "Invalid") << std::endl;
    std::cout << "Password validation: " << (validator.validatePassword("SecurePass123") ? "Valid" : "Invalid") << std::endl;
    
    // Comprehensive validation with error reporting
    auto errors = validator.validateUser("invalid-email", "123", "A", "weak");
    std::cout << "\nValidation errors:" << std::endl;
    for (const auto& error : errors) {
        std::cout << "- " << error << std::endl;
    }
    
    // Batch validation
    std::vector<std::string> emails = {"test1@example.com", "invalid-email", "test2@example.com"};
    auto emailResults = validator.validateEmails(emails);
    
    std::cout << "\nBatch email validation:" << std::endl;
    for (size_t i = 0; i < emails.size(); ++i) {
        std::cout << emails[i] << ": " << (emailResults[i] ? "Valid" : "Invalid") << std::endl;
    }
    
    // Demonstrate modern data processing
    DataProcessor processor;
    
    std::vector<std::string> names = {"alice", "BOB", "charlie", "DIANA"};
    
    // Process names to uppercase
    auto upperNames = processor.processBatch(names, StringUtils::toUpper);
    std::cout << "\nUppercase names: ";
    for (const auto& name : upperNames) {
        std::cout << name << " ";
    }
    std::cout << std::endl;
    
    // Filter names starting with 'A'
    auto filteredNames = processor.filter(names, [](const std::string& name) {
        return StringUtils::startsWith(StringUtils::toLower(name), "a");
    });
    std::cout << "Names starting with 'A': ";
    for (const auto& name : filteredNames) {
        std::cout << name << " ";
    }
    std::cout << std::endl;
    
    return 0;
} 