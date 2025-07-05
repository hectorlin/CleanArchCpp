#include <iostream>
#include <memory>
#include <fstream>
#include <string>

// RAII (Resource Acquisition Is Initialization) Principle
// Resources are acquired during object construction and released during destruction

// Bad example: Manual resource management
class BadFileHandler {
private:
    FILE* file;

public:
    BadFileHandler(const std::string& filename) {
        file = fopen(filename.c_str(), "w");
        if (!file) {
            std::cout << "Failed to open file" << std::endl;
        }
    }
    
    void write(const std::string& data) {
        if (file) {
            fputs(data.c_str(), file);
        }
    }
    
    // Problem: Need to remember to call this manually
    void close() {
        if (file) {
            fclose(file);
            file = nullptr;
        }
    }
    
    // Problem: Destructor doesn't clean up
    ~BadFileHandler() {
        // Resource leak if close() is not called!
    }
};

// Good example: RAII with automatic resource management
class GoodFileHandler {
private:
    std::unique_ptr<FILE, decltype(&fclose)> file;

public:
    GoodFileHandler(const std::string& filename) 
        : file(fopen(filename.c_str(), "w"), fclose) {
        if (!file) {
            std::cout << "Failed to open file" << std::endl;
        }
    }
    
    void write(const std::string& data) {
        if (file) {
            fputs(data.c_str(), file.get());
        }
    }
    
    // No need for manual close - RAII handles it automatically
    ~GoodFileHandler() = default;
};

// Another RAII example: Smart pointer for dynamic memory
class BadMemoryManager {
private:
    int* data;

public:
    BadMemoryManager(size_t size) {
        data = new int[size];
        std::cout << "Allocated " << size << " integers" << std::endl;
    }
    
    void setValue(size_t index, int value) {
        data[index] = value;
    }
    
    int getValue(size_t index) {
        return data[index];
    }
    
    // Problem: Need to remember to delete
    void cleanup() {
        delete[] data;
        data = nullptr;
        std::cout << "Memory deallocated" << std::endl;
    }
    
    ~BadMemoryManager() {
        // Memory leak if cleanup() is not called!
    }
};

class GoodMemoryManager {
private:
    std::unique_ptr<int[]> data;
    size_t size;

public:
    GoodMemoryManager(size_t size) 
        : data(std::make_unique<int[]>(size)), size(size) {
        std::cout << "Allocated " << size << " integers" << std::endl;
    }
    
    void setValue(size_t index, int value) {
        if (index < size) {
            data[index] = value;
        }
    }
    
    int getValue(size_t index) {
        if (index < size) {
            return data[index];
        }
        return 0;
    }
    
    // No manual cleanup needed - RAII handles it
    ~GoodMemoryManager() = default;
};

// RAII for mutex locking
class BadMutexLocker {
private:
    std::mutex* mutex;

public:
    BadMutexLocker(std::mutex* m) : mutex(m) {
        if (mutex) {
            mutex->lock();
        }
    }
    
    void unlock() {
        if (mutex) {
            mutex->unlock();
        }
    }
    
    ~BadMutexLocker() {
        // Problem: Need to remember to unlock
    }
};

// Good RAII mutex locker
class GoodMutexLocker {
private:
    std::mutex* mutex;

public:
    GoodMutexLocker(std::mutex* m) : mutex(m) {
        if (mutex) {
            mutex->lock();
        }
    }
    
    ~GoodMutexLocker() {
        if (mutex) {
            mutex->unlock();
        }
    }
};

// RAII for database connections
class DatabaseConnection {
private:
    std::string connectionString;
    bool isConnected = false;

public:
    DatabaseConnection(const std::string& connStr) : connectionString(connStr) {
        connect();
    }
    
    void connect() {
        std::cout << "Connecting to database: " << connectionString << std::endl;
        isConnected = true;
    }
    
    void disconnect() {
        if (isConnected) {
            std::cout << "Disconnecting from database" << std::endl;
            isConnected = false;
        }
    }
    
    void executeQuery(const std::string& query) {
        if (isConnected) {
            std::cout << "Executing query: " << query << std::endl;
        }
    }
    
    ~DatabaseConnection() {
        disconnect(); // RAII: automatic cleanup
    }
};

int main() {
    std::cout << "=== RAII (Resource Acquisition Is Initialization) Example ===" << std::endl;
    
    // Bad example: Manual resource management
    std::cout << "\n--- Bad Example (Manual Resource Management) ---" << std::endl;
    {
        BadFileHandler badFile("bad_example.txt");
        badFile.write("Hello, World!");
        badFile.close(); // Must remember to call this!
    }
    
    // Good example: RAII automatic resource management
    std::cout << "\n--- Good Example (RAII Automatic Management) ---" << std::endl;
    {
        GoodFileHandler goodFile("good_example.txt");
        goodFile.write("Hello, World!");
        // No need to close - RAII handles it automatically
    }
    
    // Memory management comparison
    std::cout << "\n--- Memory Management Comparison ---" << std::endl;
    
    // Bad memory management
    {
        BadMemoryManager badMem(5);
        badMem.setValue(0, 42);
        std::cout << "Value: " << badMem.getValue(0) << std::endl;
        badMem.cleanup(); // Must remember to call this!
    }
    
    // Good memory management with RAII
    {
        GoodMemoryManager goodMem(5);
        goodMem.setValue(0, 42);
        std::cout << "Value: " << goodMem.getValue(0) << std::endl;
        // No manual cleanup needed
    }
    
    // Database connection RAII
    std::cout << "\n--- Database Connection RAII ---" << std::endl;
    {
        DatabaseConnection db("localhost:5432/mydb");
        db.executeQuery("SELECT * FROM users");
        // Connection automatically closed when object goes out of scope
    }
    
    return 0;
} 