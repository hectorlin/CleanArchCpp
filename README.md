# CleanArchCpp 项目说明 / Project README

## 🏗️ 项目简介 / Project Overview

本项目是一个展示 **Clean Architecture（整洁架构）**、**现代 C++17 特性** 以及 **C++ 关键字用法** 的学习型仓库。

This project demonstrates **Clean Architecture principles**, **modern C++17 features**, and comprehensive **C++ keyword usage examples**.

---

## 📁 目录结构 / Project Structure

```
CleanArchCpp/
├── cpp/                # C++ 源码目录 / C++ source files
│   ├── clean_architecture_example.cpp  # 整洁架构示例 / Clean Architecture example
│   ├── os_detector.cpp                # 操作系统检测 / OS detector
│   ├── os_detector                    # 可执行文件 / Executable
│   └── kw_*.cpp                       # C++ 关键字示例 / C++ keyword examples
├── pattern/            # 设计模式实现 / Design pattern implementations
│   ├── dp_*.cpp
│   └── dp_*_optimized.cpp
├── bin/                # 编译后可执行文件 / Compiled executables
├── compile_all.sh      # 一键编译脚本 / Compile all script
├── README.md           # 项目说明 / This file
└── ...
```

---

## ✨ 主要内容 / Main Features

- **整洁架构分层示例 / Clean Architecture Layered Example**
- **C++ 关键字全覆盖示例 / C++ Keyword Example Collection**
- **现代 C++17 编程实践 / Modern C++17 Practices**

---

## 🏛️ 整洁架构 / Clean Architecture

- **领域层（Domain）**：业务实体与核心逻辑
- **应用层（Application）**：用例与服务
- **基础设施层（Infrastructure）**：外部接口实现
- **接口层（Interface）**：用户界面与控制器

详见 `cpp/clean_architecture_example.cpp`。

See `cpp/clean_architecture_example.cpp` for a full example.

---

## 🔤 C++ 关键字示例 / C++ Keyword Examples

`cpp/` 目录下包含所有主流 C++ 关键字的独立示例文件，每个文件演示该关键字的基本用法。

The `cpp/` directory contains standalone example files for all major C++ keywords, each demonstrating basic usage.

**示例 / Example:**
- `kw_auto.cpp`  ——  auto 关键字 / auto keyword
- `kw_constexpr.cpp`  ——  constexpr 关键字 / constexpr keyword
- `kw_virtual.cpp`  ——  virtual 关键字 / virtual keyword
- ...

---

## 🛠️ 编译与运行 / Compilation & Usage

### 编译所有示例 / Compile All Examples
```bash
./compile_all.sh
```

### 运行示例 / Run Examples
```bash
cd bin
./clean_architecture_example   # 整洁架构示例 / Clean Architecture example
./os_detector                  # 操作系统检测 / OS detector
# 关键字示例可编译后运行 / Run any compiled kw_* example
```

---

## 📚 学习建议 / Learning Path

1. **先看 C++ 关键字示例**：`cpp/kw_*.cpp`
2. **再看整洁架构示例**：`cpp/clean_architecture_example.cpp`
3. **进阶可参考 pattern/ 目录下设计模式实现**

1. **Start with C++ keyword examples**: `cpp/kw_*.cpp`
2. **Then study the Clean Architecture example**: `cpp/clean_architecture_example.cpp`
3. **For advanced topics, see design patterns in `pattern/`**

---

## 🤝 贡献 / Contributing

欢迎提交 PR，完善关键字示例或架构案例。

Contributions are welcome! Feel free to submit PRs for keyword examples or architecture improvements.

---

## 📄 许可证 / License

MIT License. 详见 LICENSE 文件。

MIT License. See LICENSE for details.

---

**Happy Coding! / 祝你编程愉快！** 