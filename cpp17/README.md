# C++17 新特性示例集 / C++17 New Features Examples

> 展示 C++17 相对于 C++11 新增的主要关键字和特性，包含完整的中英文注释和实用示例。

> Demonstrates the main new keywords and features in C++17 compared to C++11, with complete bilingual comments and practical examples.

## 🚀 快速开始 / Quick Start

```bash
# 编译所有示例
# Compile all examples
chmod +x compile_cpp17.sh
./compile_cpp17.sh

# 运行示例
# Run examples
../bin/cpp17_if_constexpr
../bin/cpp17_structured_bindings
```

## 📋 特性概览 / Features Overview

| 特性 / Feature | 文件 / File | 描述 / Description |
|---------------|-------------|-------------------|
| `if constexpr` | `kw_if_constexpr.cpp` | 编译时条件判断 |
| `inline` 变量 | `kw_inline_variables.cpp` | 头文件中直接定义变量 |
| `auto` 模板参数 | `kw_auto_template.cpp` | 自动推导模板参数类型 |
| 折叠表达式 | `kw_fold_expressions.cpp` | 简化可变参数模板 |
| 结构化绑定 | `kw_structured_bindings.cpp` | 自动解包复合类型 |
| `std::optional` | `kw_optional.cpp` | 类型安全的可选值 |
| `std::variant` | `kw_variant.cpp` | 类型安全的联合体 |
| `std::string_view` | `kw_string_view.cpp` | 零开销字符串视图 |

## 🔧 详细特性说明 / Detailed Features

### 1. if constexpr - 编译时条件判断

**问题**: C++11 中模板特化复杂且冗长
**解决方案**: C++17 的 `if constexpr` 在编译时进行条件判断

```cpp
template<typename T>
auto process(T value) {
    if constexpr (std::is_integral_v<T>) {
        return value * 2;  // 只有整数类型编译此分支
    } else if constexpr (std::is_floating_point_v<T>) {
        return value + 0.5;  // 只有浮点类型编译此分支
    } else {
        return value;  // 其他类型编译此分支
    }
}
```

**优势**:
- ✅ 编译时优化，未使用分支不生成代码
- ✅ 简化模板特化
- ✅ 提高编译效率

### 2. inline variables - 内联变量

**问题**: C++11 中头文件变量需要声明+定义分离
**解决方案**: C++17 允许在头文件中直接定义内联变量

```cpp
// 头文件中直接定义
inline const int MAX_SIZE = 100;
inline static int global_counter = 0;

template<typename T>
inline T default_value = T{};

class Config {
public:
    inline static const std::string VERSION = "1.0.0";
    inline static int instance_count = 0;
};
```

**优势**:
- ✅ 避免 ODR (One Definition Rule) 问题
- ✅ 简化头文件管理
- ✅ 支持模板变量

### 3. auto template parameters - 自动模板参数

**问题**: C++11 中非类型模板参数需要明确指定类型
**解决方案**: C++17 使用 `auto` 自动推导类型

```cpp
template<auto Value>
struct AutoTemplate {
    static constexpr auto value = Value;
    void print() const {
        std::cout << "Value: " << Value << std::endl;
    }
};

// 自动推导类型
AutoTemplate<42> int_template;      // Value 是 int
AutoTemplate<'A'> char_template;    // Value 是 char
AutoTemplate<3.14f> float_template; // Value 是 float
```

**优势**:
- ✅ 自动类型推导
- ✅ 减少模板参数声明
- ✅ 提高代码可读性

### 4. Fold Expressions - 折叠表达式

**问题**: C++11 中可变参数模板需要递归实现
**解决方案**: C++17 的折叠表达式简化操作

```cpp
// 左折叠: ((((init op pack1) op pack2) op pack3) ... op packN)
template<typename... Args>
auto sum_left(Args... args) {
    return (... + args);
}

// 右折叠: (pack1 op (pack2 op (pack3 op ... (packN op init))))
template<typename... Args>
auto sum_right(Args... args) {
    return (args + ...);
}

// 逻辑运算折叠
template<typename... Args>
bool all_true(Args... args) {
    return (... && args);
}

// 逗号折叠
template<typename... Args>
void print_all(Args... args) {
    (std::cout << ... << args) << std::endl;
}
```

**优势**:
- ✅ 简化可变参数操作
- ✅ 提高编译效率
- ✅ 代码更简洁

### 5. Structured Bindings - 结构化绑定

**问题**: C++11 中需要手动解包复合类型
**解决方案**: C++17 自动解包复合类型

```cpp
// 解包 tuple
auto [number, pi, message] = std::make_tuple(42, 3.14, "Hello");

// 解包 pair
auto [code, status] = std::make_pair(200, "OK");

// 解包数组
auto [x, y, z] = std::array{1, 2, 3};

// 解包结构体
struct Point { int x, y; std::string name; };
auto [px, py, pname] = Point{100, 200, "Origin"};

// 在循环中使用
std::map<std::string, int> scores = {{"Alice", 95}, {"Bob", 87}};
for (const auto& [name, score] : scores) {
    std::cout << name << ": " << score << std::endl;
}
```

**优势**:
- ✅ 自动解包，无需手动访问
- ✅ 支持引用和忽略元素
- ✅ 提高代码可读性

### 6. std::optional - 可选值

**问题**: C++11 中需要使用指针或特殊值表示"无值"
**解决方案**: C++17 提供类型安全的可选值

```cpp
std::optional<int> divide(int a, int b) {
    if (b == 0) {
        return std::nullopt;  // 无值
    }
    return a / b;  // 有值
}

// 使用方式
auto result = divide(10, 2);
if (result.has_value()) {
    std::cout << "Result: " << result.value() << std::endl;
}

// 提供默认值
auto user = find_user(123);
std::string name = user.value_or("Unknown");

// 链式操作
auto email = get_user_email(123);
if (email.has_value()) {
    send_email(email.value());
}
```

**优势**:
- ✅ 类型安全，避免空指针
- ✅ 语义清晰，表达意图
- ✅ 支持链式操作

### 7. std::variant - 类型安全联合体

**问题**: C++11 中 union 类型不安全，void* 类型丢失
**解决方案**: C++17 提供类型安全的联合体

```cpp
using Number = std::variant<int, double, std::string>;

// 基本使用
Number num = 42;
std::visit([](const auto& value) {
    std::cout << "Value: " << value << std::endl;
}, num);

// 类型检查
if (std::holds_alternative<int>(num)) {
    std::cout << "It's an int: " << std::get<int>(num) << std::endl;
}

// 安全访问
if (auto int_val = std::get_if<int>(&num)) {
    std::cout << "Int value: " << *int_val << std::endl;
}

// 状态机实现
using State = std::variant<IdleState, RunningState, PausedState>;
```

**优势**:
- ✅ 类型安全，编译时检查
- ✅ 支持任意类型组合
- ✅ 内存布局优化

### 8. std::string_view - 字符串视图

**问题**: C++11 中传递字符串需要拷贝或使用 const char*
**解决方案**: C++17 提供零开销的字符串视图

```cpp
void process_string(std::string_view sv) {
    // 不需要拷贝，直接使用
    std::cout << "Length: " << sv.length() << std::endl;
    std::cout << "Content: " << sv << std::endl;
}

// 从不同来源构造
std::string str = "Hello World";
process_string(str);                    // 从 string 构造
process_string("Literal string");       // 从字面量构造
process_string(str.substr(0, 5));       // 从子串构造

// 字符串操作
std::string_view sv = "Hello C++17";
auto pos = sv.find("C++");
if (pos != std::string_view::npos) {
    auto sub = sv.substr(pos, 4);
    std::cout << "Found: " << sub << std::endl;
}
```

**优势**:
- ✅ 零拷贝，提高性能
- ✅ 支持所有字符串操作
- ✅ 兼容现有 string 接口

## 🛠️ 编译和运行 / Compilation and Running

### 环境要求 / Requirements

- **编译器**: GCC 7.0+, Clang 5.0+, MSVC 2017+
- **标准**: C++17 (`-std=c++17`)
- **系统**: Linux, macOS, Windows

### 编译命令 / Compilation Commands

```bash
# 编译所有示例
./compile_cpp17.sh

# 单独编译
g++ -std=c++17 -Wall -Wextra -O2 -o ../bin/example_name example.cpp

# 调试编译
g++ -std=c++17 -Wall -Wextra -g -O0 -o ../bin/example_name_debug example.cpp
```

### 运行示例 / Running Examples

```bash
# 运行单个示例
../bin/cpp17_if_constexpr
../bin/cpp17_structured_bindings
../bin/cpp17_optional

# 运行所有示例
for exe in ../bin/cpp17_*; do
    echo "=== Running $exe ==="
    $exe
    echo ""
done
```

## 📊 性能对比 / Performance Comparison

| 特性 / Feature | C++11 方式 / C++11 Way | C++17 方式 / C++17 Way | 性能提升 / Performance Gain |
|---------------|----------------------|----------------------|---------------------------|
| 字符串传递 | `const std::string&` | `std::string_view` | 零拷贝，显著提升 |
| 可选值 | `int*` 或特殊值 | `std::optional<int>` | 类型安全，无性能损失 |
| 联合体 | `union` 或 `void*` | `std::variant` | 类型安全，内存优化 |
| 模板条件 | 特化模板 | `if constexpr` | 编译时优化 |
| 变量定义 | 头文件声明+源文件定义 | `inline` 变量 | 简化，无性能损失 |

## 🎯 最佳实践 / Best Practices

### 1. 选择合适的特性 / Choose Appropriate Features

```cpp
// ✅ 推荐：使用 string_view 进行只读字符串操作
void process_text(std::string_view text) { /* ... */ }

// ❌ 避免：不必要的 string 拷贝
void process_text(const std::string& text) { /* ... */ }
```

### 2. 错误处理 / Error Handling

```cpp
// ✅ 推荐：使用 optional 表示可能失败的操作
std::optional<int> safe_divide(int a, int b) {
    if (b == 0) return std::nullopt;
    return a / b;
}

// ❌ 避免：使用异常或特殊值
int divide(int a, int b) {
    if (b == 0) throw std::runtime_error("Division by zero");
    return a / b;
}
```

### 3. 类型安全 / Type Safety

```cpp
// ✅ 推荐：使用 variant 替代 union
using Value = std::variant<int, double, std::string>;

// ❌ 避免：使用 void* 或 union
union Value {
    int i;
    double d;
    char* s;
};
```

## 🔗 相关资源 / Related Resources

- [C++17 标准文档](https://isocpp.org/std/the-standard)
- [cppreference.com - C++17](https://en.cppreference.com/w/cpp/17)
- [C++17 特性概览](https://en.wikipedia.org/wiki/C%2B%2B17)
- [Modern C++ Features](https://github.com/AnthonyCalandra/modern-cpp-features)

## 📝 注意事项 / Notes

1. **编译器兼容性**: 确保编译器完全支持 C++17
2. **向后兼容**: 这些特性不破坏 C++11 代码
3. **性能考虑**: 大多数特性提供零开销抽象
4. **学习曲线**: 建议逐步引入新特性

## 🤝 贡献 / Contributing

欢迎提交问题报告和改进建议！

Feel free to submit issues and improvement suggestions!

---

**Happy C++17 Coding! 🚀** 