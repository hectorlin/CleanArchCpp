#!/bin/bash

# C++17 编译脚本
# C++17 Compilation Script

echo "=== Compiling C++17 Examples ==="

# 设置编译器标志
# Set compiler flags
CXX_FLAGS="-std=c++17 -Wall -Wextra -O2"

# 创建输出目录
# Create output directory
mkdir -p ../bin

# 编译所有 C++17 示例
# Compile all C++17 examples

echo "Compiling if_constexpr example..."
g++ $CXX_FLAGS -o ../bin/cpp17_if_constexpr kw_if_constexpr.cpp

echo "Compiling inline_variables example..."
g++ $CXX_FLAGS -o ../bin/cpp17_inline_variables kw_inline_variables.cpp

echo "Compiling auto_template example..."
g++ $CXX_FLAGS -o ../bin/cpp17_auto_template kw_auto_template.cpp

echo "Compiling fold_expressions example..."
g++ $CXX_FLAGS -o ../bin/cpp17_fold_expressions kw_fold_expressions.cpp

echo "Compiling structured_bindings example..."
g++ $CXX_FLAGS -o ../bin/cpp17_structured_bindings kw_structured_bindings.cpp

echo "Compiling optional example..."
g++ $CXX_FLAGS -o ../bin/cpp17_optional kw_optional.cpp

echo "Compiling variant example..."
g++ $CXX_FLAGS -o ../bin/cpp17_variant kw_variant.cpp

echo "Compiling string_view example..."
g++ $CXX_FLAGS -o ../bin/cpp17_string_view kw_string_view.cpp

echo "=== Compilation Complete ==="
echo "Executables are in ../bin/ directory"
echo ""
echo "Available C++17 examples:"
echo "  cpp17_if_constexpr      - if constexpr compile-time conditionals"
echo "  cpp17_inline_variables  - inline variables"
echo "  cpp17_auto_template     - auto template parameters"
echo "  cpp17_fold_expressions  - fold expressions for variadic templates"
echo "  cpp17_structured_bindings - structured bindings"
echo "  cpp17_optional          - std::optional for nullable values"
echo "  cpp17_variant           - std::variant for type-safe unions"
echo "  cpp17_string_view       - std::string_view for efficient strings"
echo ""
echo "Run any example with: ./bin/example_name" 