#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include <type_traits>
#include <numeric>

// Optimized KISS (Keep It Simple, Stupid) Principle Example
// Using modern C++17/20 features for better performance and readability

// Bad example: Overcomplicated solution
class OvercomplicatedCalculator {
public:
    // Overcomplicated factorial calculation
    template<typename T>
    T calculateFactorial(T n) {
        if (n < 0) {
            throw std::invalid_argument("Factorial not defined for negative numbers");
        }
        if (n == 0 || n == 1) {
            return static_cast<T>(1);
        }
        
        T result = static_cast<T>(1);
        for (T i = static_cast<T>(2); i <= n; ++i) {
            result *= i;
        }
        return result;
    }
    
    // Overcomplicated string reversal
    std::string reverseString(const std::string& input) {
        std::string result;
        result.reserve(input.length());
        
        for (auto it = input.rbegin(); it != input.rend(); ++it) {
            result.push_back(*it);
        }
        
        return result;
    }
    
    // Overcomplicated array sum
    template<typename Container>
    auto sumElements(const Container& container) -> decltype(std::declval<typename Container::value_type>() + std::declval<typename Container::value_type>()) {
        using ValueType = typename Container::value_type;
        ValueType sum = ValueType{};
        
        for (const auto& element : container) {
            sum += element;
        }
        
        return sum;
    }
    
    // Overcomplicated number classification
    std::string classifyNumber(int number) {
        if (number == 0) {
            return "Zero";
        } else if (number > 0) {
            if (number % 2 == 0) {
                return "Positive Even";
            } else {
                return "Positive Odd";
            }
        } else {
            if (number % 2 == 0) {
                return "Negative Even";
            } else {
                return "Negative Odd";
            }
        }
    }
};

// Optimized example: Simple and straightforward solutions
// Using modern C++ features for better performance and readability

// Simple calculator with modern C++ features
class SimpleCalculator {
public:
    // Simple factorial using recursion (for small numbers)
    [[nodiscard]] constexpr unsigned long long factorial(unsigned int n) const noexcept {
        return (n <= 1) ? 1 : n * factorial(n - 1);
    }
    
    // Simple factorial using iteration (for larger numbers)
    [[nodiscard]] unsigned long long factorialIterative(unsigned int n) const {
        if (n <= 1) return 1;
        
        unsigned long long result = 1;
        for (unsigned int i = 2; i <= n; ++i) {
            result *= i;
        }
        return result;
    }
    
    // Simple string reversal using std::reverse
    [[nodiscard]] std::string reverseString(std::string_view str) const {
        std::string result(str);
        std::reverse(result.begin(), result.end());
        return result;
    }
    
    // Simple sum using std::accumulate
    template<typename Container>
    [[nodiscard]] auto sum(const Container& container) const {
        using ValueType = typename Container::value_type;
        return std::accumulate(container.begin(), container.end(), ValueType{});
    }
    
    // Simple number classification using ternary operators
    [[nodiscard]] std::string_view classifyNumber(int number) const noexcept {
        if (number == 0) return "Zero";
        return (number > 0) ? 
               (number % 2 == 0 ? "Positive Even" : "Positive Odd") :
               (number % 2 == 0 ? "Negative Even" : "Negative Odd");
    }
    
    // Simple maximum finder
    template<typename Container>
    [[nodiscard]] auto findMax(const Container& container) const {
        return *std::max_element(container.begin(), container.end());
    }
    
    // Simple minimum finder
    template<typename Container>
    [[nodiscard]] auto findMin(const Container& container) const {
        return *std::min_element(container.begin(), container.end());
    }
    
    // Simple average calculator
    template<typename Container>
    [[nodiscard]] double average(const Container& container) const {
        if (container.empty()) return 0.0;
        return static_cast<double>(sum(container)) / container.size();
    }
};

// Simple data processor using modern C++ features
class SimpleDataProcessor {
public:
    // Simple filtering using std::copy_if
    template<typename Container, typename Predicate>
    [[nodiscard]] auto filter(const Container& container, Predicate pred) const {
        using ValueType = typename Container::value_type;
        std::vector<ValueType> result;
        std::copy_if(container.begin(), container.end(), std::back_inserter(result), pred);
        return result;
    }
    
    // Simple transformation using std::transform
    template<typename Container, typename Transform>
    [[nodiscard]] auto transform(const Container& container, Transform func) const {
        using InputType = typename Container::value_type;
        using OutputType = std::invoke_result_t<Transform, InputType>;
        
        std::vector<OutputType> result;
        result.reserve(container.size());
        std::transform(container.begin(), container.end(), std::back_inserter(result), func);
        return result;
    }
    
    // Simple counting using std::count_if
    template<typename Container, typename Predicate>
    [[nodiscard]] size_t count(const Container& container, Predicate pred) const {
        return std::count_if(container.begin(), container.end(), pred);
    }
    
    // Simple sorting (in-place)
    template<typename Container>
    void sort(Container& container) const {
        std::sort(container.begin(), container.end());
    }
    
    // Simple sorting with custom comparator
    template<typename Container, typename Compare>
    void sort(Container& container, Compare comp) const {
        std::sort(container.begin(), container.end(), comp);
    }
};

// Simple string utilities
class SimpleStringUtils {
public:
    // Simple case conversion
    [[nodiscard]] static std::string toUpper(std::string_view str) {
        std::string result(str);
        std::transform(result.begin(), result.end(), result.begin(), ::toupper);
        return result;
    }
    
    [[nodiscard]] static std::string toLower(std::string_view str) {
        std::string result(str);
        std::transform(result.begin(), result.end(), result.begin(), ::tolower);
        return result;
    }
    
    // Simple string trimming
    [[nodiscard]] static std::string trim(std::string_view str) {
        auto start = str.find_first_not_of(" \t\n\r");
        if (start == std::string_view::npos) return "";
        
        auto end = str.find_last_not_of(" \t\n\r");
        return std::string(str.substr(start, end - start + 1));
    }
    
    // Simple string splitting
    [[nodiscard]] static std::vector<std::string> split(std::string_view str, char delimiter) {
        std::vector<std::string> result;
        size_t start = 0;
        size_t end = str.find(delimiter);
        
        while (end != std::string_view::npos) {
            result.emplace_back(str.substr(start, end - start));
            start = end + 1;
            end = str.find(delimiter, start);
        }
        
        result.emplace_back(str.substr(start));
        return result;
    }
    
    // Simple string joining
    [[nodiscard]] static std::string join(const std::vector<std::string>& strings, std::string_view separator) {
        if (strings.empty()) return "";
        
        std::string result = strings[0];
        for (size_t i = 1; i < strings.size(); ++i) {
            result += separator;
            result += strings[i];
        }
        return result;
    }
};

// Simple number utilities
class SimpleNumberUtils {
public:
    // Simple prime check
    [[nodiscard]] static bool isPrime(unsigned int n) {
        if (n < 2) return false;
        if (n == 2) return true;
        if (n % 2 == 0) return false;
        
        for (unsigned int i = 3; i * i <= n; i += 2) {
            if (n % i == 0) return false;
        }
        return true;
    }
    
    // Simple GCD calculation
    [[nodiscard]] static unsigned int gcd(unsigned int a, unsigned int b) {
        while (b != 0) {
            unsigned int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }
    
    // Simple LCM calculation
    [[nodiscard]] static unsigned int lcm(unsigned int a, unsigned int b) {
        return (a / gcd(a, b)) * b;
    }
    
    // Simple power calculation
    [[nodiscard]] static double power(double base, int exponent) {
        if (exponent == 0) return 1.0;
        if (exponent < 0) return 1.0 / power(base, -exponent);
        
        double result = 1.0;
        while (exponent > 0) {
            if (exponent % 2 == 1) result *= base;
            base *= base;
            exponent /= 2;
        }
        return result;
    }
};

int main() {
    std::cout << "=== Optimized KISS (Keep It Simple, Stupid) Principle Example ===" << std::endl;
    
    // Bad example: Overcomplicated solutions
    std::cout << "\n--- Bad Example (Overcomplicated) ---" << std::endl;
    OvercomplicatedCalculator badCalc;
    
    std::cout << "Factorial of 5: " << badCalc.calculateFactorial(5) << std::endl;
    std::cout << "Reverse of 'hello': " << badCalc.reverseString("hello") << std::endl;
    
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    std::cout << "Sum of numbers: " << badCalc.sumElements(numbers) << std::endl;
    std::cout << "Classification of 7: " << badCalc.classifyNumber(7) << std::endl;
    
    // Optimized example: Simple and straightforward solutions
    std::cout << "\n--- Optimized Example (Simple Solutions) ---" << std::endl;
    
    SimpleCalculator calc;
    SimpleDataProcessor processor;
    SimpleStringUtils stringUtils;
    SimpleNumberUtils numberUtils;
    
    // Simple calculations
    std::cout << "Factorial of 5: " << calc.factorial(5) << std::endl;
    std::cout << "Reverse of 'hello': " << calc.reverseString("hello") << std::endl;
    std::cout << "Sum of numbers: " << calc.sum(numbers) << std::endl;
    std::cout << "Classification of 7: " << calc.classifyNumber(7) << std::endl;
    
    // Simple data processing
    std::vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    auto evenNumbers = processor.filter(data, [](int n) { return n % 2 == 0; });
    std::cout << "Even numbers: ";
    for (int n : evenNumbers) std::cout << n << " ";
    std::cout << std::endl;
    
    auto doubled = processor.transform(data, [](int n) { return n * 2; });
    std::cout << "Doubled numbers: ";
    for (int n : doubled) std::cout << n << " ";
    std::cout << std::endl;
    
    std::cout << "Count of even numbers: " << processor.count(data, [](int n) { return n % 2 == 0; }) << std::endl;
    std::cout << "Maximum: " << calc.findMax(data) << std::endl;
    std::cout << "Minimum: " << calc.findMin(data) << std::endl;
    std::cout << "Average: " << calc.average(data) << std::endl;
    
    // Simple string operations
    std::string text = "  Hello World  ";
    std::cout << "Original: '" << text << "'" << std::endl;
    std::cout << "Uppercase: '" << stringUtils.toUpper(text) << "'" << std::endl;
    std::cout << "Lowercase: '" << stringUtils.toLower(text) << "'" << std::endl;
    std::cout << "Trimmed: '" << stringUtils.trim(text) << "'" << std::endl;
    
    std::string csv = "apple,banana,cherry";
    auto fruits = stringUtils.split(csv, ',');
    std::cout << "Split result: ";
    for (const auto& fruit : fruits) std::cout << "'" << fruit << "' ";
    std::cout << std::endl;
    
    std::cout << "Joined: '" << stringUtils.join(fruits, " | ") << "'" << std::endl;
    
    // Simple number operations
    std::cout << "Is 17 prime? " << (numberUtils.isPrime(17) ? "Yes" : "No") << std::endl;
    std::cout << "GCD of 48 and 18: " << numberUtils.gcd(48, 18) << std::endl;
    std::cout << "LCM of 12 and 18: " << numberUtils.lcm(12, 18) << std::endl;
    std::cout << "2^10 = " << numberUtils.power(2, 10) << std::endl;
    
    return 0;
} 