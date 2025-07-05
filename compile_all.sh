#!/bin/bash

# CleanArchCpp - Compile All C++ Files Script
# 编译所有C++文件的脚本

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Compiler settings
CXX="g++"
CXXFLAGS="-std=c++17 -Wall -Wextra -O2"
INCLUDE_DIRS="-I."

# Counters
TOTAL_FILES=0
COMPILED_FILES=0
FAILED_FILES=0

echo -e "${BLUE}========================================${NC}"
echo -e "${BLUE}  CleanArchCpp - Compile All C++ Files${NC}"
echo -e "${BLUE}========================================${NC}"
echo

# Function to compile a single file
compile_file() {
    local file="$1"
    local output_name="${file%.cpp}"
    
    echo -e "${YELLOW}Compiling: ${file}${NC}"
    
    if $CXX $CXXFLAGS $INCLUDE_DIRS -o "$output_name" "$file" 2>/dev/null; then
        echo -e "${GREEN}✓ Success: ${output_name}${NC}"
        ((COMPILED_FILES++))
        return 0
    else
        echo -e "${RED}✗ Failed: ${file}${NC}"
        ((FAILED_FILES++))
        return 1
    fi
}

# Function to compile files in a directory
compile_directory() {
    local dir="$1"
    local pattern="$2"
    
    if [ -d "$dir" ]; then
        echo -e "${BLUE}Compiling files in ${dir}/${pattern}${NC}"
        echo
        
        for file in "$dir"/$pattern; do
            if [ -f "$file" ]; then
                compile_file "$file"
                ((TOTAL_FILES++))
                echo
            fi
        done
    else
        echo -e "${RED}Directory ${dir} not found${NC}"
    fi
}

# Create output directory for executables
mkdir -p bin

# Compile cpp directory files
echo -e "${BLUE}=== Compiling cpp/ directory ===${NC}"
echo

# Clean Architecture example
if [ -f "cpp/clean_architecture_example.cpp" ]; then
    compile_file "cpp/clean_architecture_example.cpp"
    mv clean_architecture_example bin/ 2>/dev/null
    echo
fi

# OS detector
if [ -f "cpp/os_detector.cpp" ]; then
    compile_file "cpp/os_detector.cpp"
    mv os_detector bin/ 2>/dev/null
    echo
fi

# Design pattern files
compile_directory "cpp" "dp_*.cpp"
for file in cpp/dp_*.cpp; do
    if [ -f "$file" ]; then
        mv "${file%.cpp}" bin/ 2>/dev/null
    fi
done

# Keyword files
compile_directory "cpp" "kw_*.cpp"
for file in cpp/kw_*.cpp; do
    if [ -f "$file" ]; then
        mv "${file%.cpp}" bin/ 2>/dev/null
    fi
done

# Compile pattern directory files
echo -e "${BLUE}=== Compiling pattern/ directory ===${NC}"
echo

# Basic design pattern files
compile_directory "pattern" "dp_*.cpp"
for file in pattern/dp_*.cpp; do
    if [ -f "$file" ]; then
        mv "${file%.cpp}" bin/ 2>/dev/null
    fi
done

# Optimized design pattern files
compile_directory "pattern" "dp_*_optimized.cpp"
for file in pattern/dp_*_optimized.cpp; do
    if [ -f "$file" ]; then
        mv "${file%.cpp}" bin/ 2>/dev/null
    fi
done

# Summary
echo -e "${BLUE}========================================${NC}"
echo -e "${BLUE}  Compilation Summary${NC}"
echo -e "${BLUE}========================================${NC}"
echo -e "${YELLOW}Total files processed: ${TOTAL_FILES}${NC}"
echo -e "${GREEN}Successfully compiled: ${COMPILED_FILES}${NC}"
echo -e "${RED}Failed to compile: ${FAILED_FILES}${NC}"
echo

if [ $FAILED_FILES -eq 0 ]; then
    echo -e "${GREEN}🎉 All files compiled successfully!${NC}"
    echo -e "${BLUE}Executables are in the bin/ directory${NC}"
else
    echo -e "${YELLOW}⚠️  Some files failed to compile. Check the errors above.${NC}"
fi

echo
echo -e "${BLUE}To run all executables:${NC}"
echo -e "${YELLOW}cd bin && for file in *; do echo \"=== Running \$file ===\"; ./\$file; echo; done${NC}"
echo 