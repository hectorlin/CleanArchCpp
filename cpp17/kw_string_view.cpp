#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <algorithm>

// C++17: std::string_view - 字符串视图
// C++17: std::string_view - efficient string handling without copying

// C++17 之前，传递字符串需要复制或使用 const char*
// Before C++17, passing strings required copying or using const char*
// C++17 的 std::string_view 提供了零开销的字符串视图
// C++17 std::string_view provides zero-overhead string views

// 使用 string_view 的函数
// Function using string_view
void print_string(std::string_view sv) {
    std::cout << "String: " << sv << " (length: " << sv.length() << ")" << std::endl;
}

// 字符串查找函数
// String search function
std::string_view find_substring(std::string_view haystack, std::string_view needle) {
    auto pos = haystack.find(needle);
    if (pos != std::string_view::npos) {
        return haystack.substr(pos, needle.length());
    }
    return std::string_view{};
}

// 字符串分割函数
// String split function
std::vector<std::string_view> split(std::string_view str, std::string_view delimiter) {
    std::vector<std::string_view> result;
    size_t start = 0;
    size_t end = str.find(delimiter);
    
    while (end != std::string_view::npos) {
        result.push_back(str.substr(start, end - start));
        start = end + delimiter.length();
        end = str.find(delimiter, start);
    }
    
    result.push_back(str.substr(start));
    return result;
}

// 字符串比较函数
// String comparison function
bool starts_with(std::string_view str, std::string_view prefix) {
    return str.substr(0, prefix.length()) == prefix;
}

bool ends_with(std::string_view str, std::string_view suffix) {
    if (str.length() < suffix.length()) return false;
    return str.substr(str.length() - suffix.length()) == suffix;
}

// 使用 string_view 的类
// Class using string_view
class TextProcessor {
public:
    // 构造函数接受 string_view
    // Constructor accepts string_view
    TextProcessor(std::string_view text) : text_(text) {}
    
    // 查找单词
    // Find word
    std::string_view find_word(std::string_view word) const {
        auto pos = text_.find(word);
        if (pos != std::string_view::npos) {
            return text_.substr(pos, word.length());
        }
        return std::string_view{};
    }
    
    // 统计单词出现次数
    // Count word occurrences
    size_t count_occurrences(std::string_view word) const {
        size_t count = 0;
        size_t pos = 0;
        
        while ((pos = text_.find(word, pos)) != std::string_view::npos) {
            count++;
            pos += word.length();
        }
        
        return count;
    }
    
    // 获取所有行
    // Get all lines
    std::vector<std::string_view> get_lines() const {
        return split(text_, "\n");
    }
    
    // 获取所有单词
    // Get all words
    std::vector<std::string_view> get_words() const {
        return split(text_, " ");
    }
    
    // 打印信息
    // Print information
    void print_info() const {
        std::cout << "Text length: " << text_.length() << std::endl;
        std::cout << "Text: " << text_ << std::endl;
    }
    
private:
    std::string_view text_;
};

// 使用 string_view 进行字符串处理
// String processing using string_view
class StringAnalyzer {
public:
    // 分析字符串统计信息
    // Analyze string statistics
    struct Stats {
        size_t length;
        size_t word_count;
        size_t line_count;
        size_t char_count;
    };
    
    static Stats analyze(std::string_view text) {
        Stats stats{};
        stats.length = text.length();
        
        // 统计字符数（不包括空格）
        // Count characters (excluding spaces)
        stats.char_count = std::count_if(text.begin(), text.end(), 
            [](char c) { return !std::isspace(c); });
        
        // 统计行数
        // Count lines
        stats.line_count = std::count(text.begin(), text.end(), '\n') + 1;
        
        // 统计单词数
        // Count words
        auto words = split(text, " ");
        stats.word_count = words.size();
        
        return stats;
    }
    
    // 查找最长的单词
    // Find longest word
    static std::string_view find_longest_word(std::string_view text) {
        auto words = split(text, " ");
        if (words.empty()) return std::string_view{};
        
        auto longest = std::max_element(words.begin(), words.end(),
            [](std::string_view a, std::string_view b) {
                return a.length() < b.length();
            });
        
        return *longest;
    }
    
    // 查找最短的单词
    // Find shortest word
    static std::string_view find_shortest_word(std::string_view text) {
        auto words = split(text, " ");
        if (words.empty()) return std::string_view{};
        
        auto shortest = std::min_element(words.begin(), words.end(),
            [](std::string_view a, std::string_view b) {
                return a.length() < b.length();
            });
        
        return *shortest;
    }
};

// 使用 string_view 进行模式匹配
// Pattern matching using string_view
class PatternMatcher {
public:
    // 检查是否匹配模式
    // Check if matches pattern
    static bool matches_pattern(std::string_view text, std::string_view pattern) {
        if (pattern.empty()) return text.empty();
        if (text.empty()) return pattern == "*";
        
        if (pattern[0] == '*') {
            // 通配符匹配
            // Wildcard matching
            return matches_pattern(text, pattern.substr(1)) ||
                   matches_pattern(text.substr(1), pattern);
        }
        
        if (pattern[0] == '?' || pattern[0] == text[0]) {
            return matches_pattern(text.substr(1), pattern.substr(1));
        }
        
        return false;
    }
    
    // 查找所有匹配的模式
    // Find all matching patterns
    static std::vector<std::string_view> find_matches(std::string_view text, 
                                                     std::vector<std::string_view> patterns) {
        std::vector<std::string_view> matches;
        
        for (const auto& pattern : patterns) {
            if (matches_pattern(text, pattern)) {
                matches.push_back(text);
            }
        }
        
        return matches;
    }
};

int main() {
    std::cout << "=== C++17 std::string_view Demo ===" << std::endl;
    
    // 基本用法
    // Basic usage
    std::string str = "Hello, C++17 World!";
    std::string_view sv1 = str;
    std::string_view sv2 = "Another string";
    std::string_view sv3 = str.substr(0, 5);  // "Hello"
    
    print_string(sv1);
    print_string(sv2);
    print_string(sv3);
    
    // 字符串查找
    // String search
    auto found = find_substring(sv1, "C++17");
    if (!found.empty()) {
        std::cout << "Found: " << found << std::endl;
    }
    
    // 字符串分割
    // String split
    auto words = split(sv1, " ");
    std::cout << "Words: ";
    for (const auto& word : words) {
        std::cout << "[" << word << "] ";
    }
    std::cout << std::endl;
    
    // 字符串比较
    // String comparison
    std::cout << "Starts with 'Hello': " << std::boolalpha << starts_with(sv1, "Hello") << std::endl;
    std::cout << "Ends with '!': " << std::boolalpha << ends_with(sv1, "!") << std::endl;
    
    // 使用类
    // Using classes
    std::string text = "This is a sample text.\nIt has multiple lines.\nAnd some words.";
    TextProcessor processor(text);
    
    processor.print_info();
    
    auto word = processor.find_word("sample");
    if (!word.empty()) {
        std::cout << "Found word: " << word << std::endl;
    }
    
    std::cout << "Occurrences of 'is': " << processor.count_occurrences("is") << std::endl;
    
    auto lines = processor.get_lines();
    std::cout << "Lines:" << std::endl;
    for (size_t i = 0; i < lines.size(); ++i) {
        std::cout << "Line " << (i + 1) << ": " << lines[i] << std::endl;
    }
    
    auto all_words = processor.get_words();
    std::cout << "All words:" << std::endl;
    for (const auto& w : all_words) {
        std::cout << "[" << w << "] ";
    }
    std::cout << std::endl;
    
    // 字符串分析
    // String analysis
    auto stats = StringAnalyzer::analyze(text);
    std::cout << "Text statistics:" << std::endl;
    std::cout << "Length: " << stats.length << std::endl;
    std::cout << "Characters: " << stats.char_count << std::endl;
    std::cout << "Words: " << stats.word_count << std::endl;
    std::cout << "Lines: " << stats.line_count << std::endl;
    
    auto longest = StringAnalyzer::find_longest_word(text);
    auto shortest = StringAnalyzer::find_shortest_word(text);
    
    std::cout << "Longest word: " << longest << std::endl;
    std::cout << "Shortest word: " << shortest << std::endl;
    
    // 模式匹配
    // Pattern matching
    std::vector<std::string_view> patterns = {"*sample*", "*text*", "*xyz*"};
    auto matches = PatternMatcher::find_matches(text, patterns);
    
    std::cout << "Pattern matches:" << std::endl;
    for (const auto& match : matches) {
        std::cout << "Match: " << match << std::endl;
    }
    
    // 性能比较：string_view vs string
    // Performance comparison: string_view vs string
    std::cout << "\nPerformance test:" << std::endl;
    
    // 使用 string_view（零拷贝）
    // Using string_view (zero copy)
    std::string_view large_text = "This is a very long text that we want to process efficiently";
    for (int i = 0; i < 1000; ++i) {
        auto words = split(large_text, " ");
        (void)words;  // 避免编译器优化
    }
    std::cout << "string_view processing completed" << std::endl;
    
    // 使用 string（需要拷贝）
    // Using string (requires copy)
    std::string large_string = "This is a very long text that we want to process efficiently";
    for (int i = 0; i < 1000; ++i) {
        auto words = split(large_string, " ");
        (void)words;  // 避免编译器优化
    }
    std::cout << "string processing completed" << std::endl;
    
    return 0;
} 