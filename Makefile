CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2

# Detect OS for conditional compilation
ifeq ($(OS),Windows_NT)
    OS_TARGET = os_detector.exe
    CXXFLAGS += -D_WIN32
else
    OS_TARGET = os_detector
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Darwin)
        CXXFLAGS += -D__APPLE__
    else ifeq ($(UNAME_S),Linux)
        CXXFLAGS += -D__linux__
    endif
endif

# Clean Architecture targets
CLEAN_ARCH_TARGET = clean_architecture_example

all: $(OS_TARGET) $(CLEAN_ARCH_TARGET)

$(OS_TARGET): os_detector.cpp
	$(CXX) $(CXXFLAGS) -o $(OS_TARGET) os_detector.cpp

$(CLEAN_ARCH_TARGET): clean_architecture_example.cpp
	$(CXX) $(CXXFLAGS) -o $(CLEAN_ARCH_TARGET) clean_architecture_example.cpp

clean:
	rm -f $(OS_TARGET) $(CLEAN_ARCH_TARGET) *.o

run-os: $(OS_TARGET)
	./$(OS_TARGET)

run-clean-arch: $(CLEAN_ARCH_TARGET)
	./$(CLEAN_ARCH_TARGET)

.PHONY: all clean run-os run-clean-arch 