#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <fstream>
#include <mutex>
#include <thread>
#include <chrono>
#include <map>

// Optimized RAII (Resource Acquisition Is Initialization) Principle Example
// Using modern C++17/20 features for better performance and safety

// Bad example: Manual resource management
class BadFileHandler {
public:
    BadFileHandler(const std::string& filename) {
        file_ = fopen(filename.c_str(), "r");
        if (!file_) {
            std::cerr << "Failed to open file: " << filename << std::endl;
        }
    }
    
    ~BadFileHandler() {
        if (file_) {
            fclose(file_);
        }
    }
    
    void readData() {
        if (file_) {
            char buffer[1024];
            while (fgets(buffer, sizeof(buffer), file_)) {
                std::cout << "Read: " << buffer;
            }
        }
    }
    
    // Problem: What if an exception is thrown? File might not be closed properly
    void processWithException() {
        if (file_) {
            throw std::runtime_error("Something went wrong!");
            // File won't be closed if exception is thrown
        }
    }

private:
    FILE* file_;
};

// Bad example: Manual memory management
class BadMemoryManager {
public:
    BadMemoryManager(size_t size) {
        data_ = new int[size];
        size_ = size;
        std::cout << "Allocated " << size << " integers" << std::endl;
    }
    
    ~BadMemoryManager() {
        delete[] data_;
        std::cout << "Deallocated memory" << std::endl;
    }
    
    void fillData() {
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = static_cast<int>(i);
        }
    }
    
    // Problem: What if an exception is thrown? Memory might leak
    void processWithException() {
        throw std::runtime_error("Memory processing error!");
        // Memory won't be deallocated if exception is thrown
    }

private:
    int* data_;
    size_t size_;
};

// Optimized example: RAII with modern C++ features
// Using smart pointers, RAII classes, and exception safety

// Modern file handler using RAII
class ModernFileHandler {
public:
    explicit ModernFileHandler(const std::string& filename) 
        : filename_(filename) {
        file_.open(filename);
        if (!file_.is_open()) {
            throw std::runtime_error("Failed to open file: " + filename);
        }
        std::cout << "File opened: " << filename << std::endl;
    }
    
    // Destructor automatically closes the file
    ~ModernFileHandler() {
        if (file_.is_open()) {
            file_.close();
            std::cout << "File closed: " << filename_ << std::endl;
        }
    }
    
    // Move semantics for better performance
    ModernFileHandler(ModernFileHandler&& other) noexcept
        : file_(std::move(other.file_)), filename_(std::move(other.filename_)) {}
    
    ModernFileHandler& operator=(ModernFileHandler&& other) noexcept {
        if (this != &other) {
            file_ = std::move(other.file_);
            filename_ = std::move(other.filename_);
        }
        return *this;
    }
    
    // Delete copy operations
    ModernFileHandler(const ModernFileHandler&) = delete;
    ModernFileHandler& operator=(const ModernFileHandler&) = delete;
    
    // Safe file operations
    std::string readLine() {
        std::string line;
        if (std::getline(file_, line)) {
            return line;
        }
        return "";
    }
    
    void writeLine(const std::string& line) {
        file_ << line << std::endl;
    }
    
    [[nodiscard]] bool isOpen() const noexcept {
        return file_.is_open();
    }
    
    // Exception-safe operations
    void processWithException() {
        if (!file_.is_open()) {
            throw std::runtime_error("File is not open");
        }
        throw std::runtime_error("Processing error");
        // File will be automatically closed by destructor
    }

private:
    std::fstream file_;
    std::string filename_;
};

// Modern memory manager using RAII
class ModernMemoryManager {
public:
    explicit ModernMemoryManager(size_t size) 
        : data_(std::make_unique<int[]>(size)), size_(size) {
        std::cout << "Allocated " << size << " integers using RAII" << std::endl;
    }
    
    // Destructor automatically deallocates memory
    ~ModernMemoryManager() = default; // unique_ptr handles cleanup
    
    // Move semantics
    ModernMemoryManager(ModernMemoryManager&&) = default;
    ModernMemoryManager& operator=(ModernMemoryManager&&) = default;
    
    // Delete copy operations
    ModernMemoryManager(const ModernMemoryManager&) = delete;
    ModernMemoryManager& operator=(const ModernMemoryManager&) = delete;
    
    void fillData() {
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = static_cast<int>(i);
        }
    }
    
    [[nodiscard]] int getValue(size_t index) const {
        if (index < size_) {
            return data_[index];
        }
        throw std::out_of_range("Index out of range");
    }
    
    void setValue(size_t index, int value) {
        if (index < size_) {
            data_[index] = value;
        } else {
            throw std::out_of_range("Index out of range");
        }
    }
    
    [[nodiscard]] size_t size() const noexcept {
        return size_;
    }
    
    // Exception-safe operations
    void processWithException() {
        throw std::runtime_error("Memory processing error");
        // Memory will be automatically deallocated by unique_ptr
    }

private:
    std::unique_ptr<int[]> data_;
    size_t size_;
};

// RAII mutex wrapper
class ScopedLock {
public:
    explicit ScopedLock(std::mutex& mutex) : mutex_(mutex) {
        mutex_.lock();
        std::cout << "Mutex locked" << std::endl;
    }
    
    ~ScopedLock() {
        mutex_.unlock();
        std::cout << "Mutex unlocked" << std::endl;
    }
    
    // Delete copy operations
    ScopedLock(const ScopedLock&) = delete;
    ScopedLock& operator=(const ScopedLock&) = delete;

private:
    std::mutex& mutex_;
};

// RAII timer for performance measurement
class ScopedTimer {
public:
    ScopedTimer(const std::string& name) 
        : name_(name), start_(std::chrono::high_resolution_clock::now()) {
        std::cout << "Timer started: " << name_ << std::endl;
    }
    
    ~ScopedTimer() {
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start_);
        std::cout << "Timer " << name_ << " took " << duration.count() << " microseconds" << std::endl;
    }
    
    // Delete copy operations
    ScopedTimer(const ScopedTimer&) = delete;
    ScopedTimer& operator=(const ScopedTimer&) = delete;

private:
    std::string name_;
    std::chrono::high_resolution_clock::time_point start_;
};

// RAII connection wrapper
class DatabaseConnection {
public:
    DatabaseConnection(const std::string& connectionString) 
        : connectionString_(connectionString), connected_(false) {
        connect();
    }
    
    ~DatabaseConnection() {
        disconnect();
    }
    
    // Move semantics
    DatabaseConnection(DatabaseConnection&& other) noexcept
        : connectionString_(std::move(other.connectionString_))
        , connected_(other.connected_) {
        other.connected_ = false;
    }
    
    DatabaseConnection& operator=(DatabaseConnection&& other) noexcept {
        if (this != &other) {
            disconnect();
            connectionString_ = std::move(other.connectionString_);
            connected_ = other.connected_;
            other.connected_ = false;
        }
        return *this;
    }
    
    // Delete copy operations
    DatabaseConnection(const DatabaseConnection&) = delete;
    DatabaseConnection& operator=(const DatabaseConnection&) = delete;
    
    void executeQuery(const std::string& query) {
        if (!connected_) {
            throw std::runtime_error("Not connected to database");
        }
        std::cout << "Executing query: " << query << std::endl;
    }
    
    [[nodiscard]] bool isConnected() const noexcept {
        return connected_;
    }

private:
    void connect() {
        std::cout << "Connecting to database: " << connectionString_ << std::endl;
        connected_ = true;
    }
    
    void disconnect() {
        if (connected_) {
            std::cout << "Disconnecting from database: " << connectionString_ << std::endl;
            connected_ = false;
        }
    }

private:
    std::string connectionString_;
    bool connected_;
};

// Modern resource manager using RAII
class ResourceManager {
public:
    ResourceManager() = default;
    
    // RAII-managed resources
    void createFile(const std::string& filename) {
        files_.emplace_back(filename);
    }
    
    void createMemory(size_t size) {
        memory_.emplace_back(size);
    }
    
    void createConnection(const std::string& connectionString) {
        connections_.emplace_back(connectionString);
    }
    
    // Process resources with exception safety
    void processAll() {
        {
            ScopedTimer timer("File processing");
            for (auto& file : files_) {
                file.writeLine("Processing data");
            }
        }
        
        {
            ScopedTimer timer("Memory processing");
            for (auto& mem : memory_) {
                mem.fillData();
            }
        }
        
        {
            ScopedTimer timer("Database processing");
            for (auto& conn : connections_) {
                conn.executeQuery("SELECT * FROM data");
            }
        }
    }
    
    // Exception-safe operations
    void processWithExceptions() {
        try {
            for (auto& file : files_) {
                file.processWithException();
            }
        } catch (const std::exception& e) {
            std::cout << "Exception caught: " << e.what() << std::endl;
            // All resources are automatically cleaned up
        }
    }

private:
    std::vector<ModernFileHandler> files_;
    std::vector<ModernMemoryManager> memory_;
    std::vector<DatabaseConnection> connections_;
};

// Thread-safe resource manager using RAII
class ThreadSafeResourceManager {
public:
    void addResource(const std::string& name, const std::string& data) {
        ScopedLock lock(mutex_);
        resources_[name] = data;
        std::cout << "Added resource: " << name << std::endl;
    }
    
    std::string getResource(const std::string& name) {
        ScopedLock lock(mutex_);
        auto it = resources_.find(name);
        if (it != resources_.end()) {
            return it->second;
        }
        return "";
    }
    
    void removeResource(const std::string& name) {
        ScopedLock lock(mutex_);
        if (resources_.erase(name) > 0) {
            std::cout << "Removed resource: " << name << std::endl;
        }
    }

private:
    std::map<std::string, std::string> resources_;
    mutable std::mutex mutex_;
};

int main() {
    std::cout << "=== Optimized RAII (Resource Acquisition Is Initialization) Principle Example ===" << std::endl;
    
    // Bad example: Manual resource management
    std::cout << "\n--- Bad Example (Manual Resource Management) ---" << std::endl;
    try {
        BadFileHandler badFile("nonexistent.txt");
        badFile.processWithException();
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    
    try {
        BadMemoryManager badMem(1000);
        badMem.processWithException();
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    
    // Optimized example: RAII with modern C++ features
    std::cout << "\n--- Optimized Example (RAII Applied) ---" << std::endl;
    
    ResourceManager manager;
    
    // Create resources (automatically managed)
    manager.createFile("test.txt");
    manager.createMemory(1000);
    manager.createConnection("localhost:5432");
    
    // Process resources with automatic cleanup
    manager.processAll();
    
    // Demonstrate exception safety
    std::cout << "\n--- Exception Safety Demo ---" << std::endl;
    manager.processWithExceptions();
    
    // Thread-safe resource management
    std::cout << "\n--- Thread-Safe Resource Management ---" << std::endl;
    ThreadSafeResourceManager threadSafeManager;
    
    threadSafeManager.addResource("config", "database=localhost");
    threadSafeManager.addResource("user", "admin");
    
    std::cout << "Config: " << threadSafeManager.getResource("config") << std::endl;
    std::cout << "User: " << threadSafeManager.getResource("user") << std::endl;
    
    threadSafeManager.removeResource("user");
    
    // Demonstrate move semantics
    std::cout << "\n--- Move Semantics Demo ---" << std::endl;
    {
        ModernFileHandler file1("test1.txt");
        file1.writeLine("Hello from file1");
        
        ModernFileHandler file2 = std::move(file1); // Move ownership
        file2.writeLine("Hello from file2");
        // file1 is now in moved-from state, file2 owns the resource
    } // Both files are automatically closed
    
    return 0;
} 