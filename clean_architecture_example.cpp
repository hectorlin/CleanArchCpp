#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <algorithm>

// C++11 compatibility: std::make_unique was introduced in C++14
namespace std {
    template<typename T, typename... Args>
    std::unique_ptr<T> make_unique(Args&&... args) {
        return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
    }
}

// ============================================================================
// ENTITIES (Domain Layer) - 实体层
// ============================================================================

// User entity - 用户实体
class User {
private:
    int id_;
    std::string name_;
    std::string email_;

public:
    User(int id, const std::string& name, const std::string& email)
        : id_(id), name_(name), email_(email) {}

    int getId() const { return id_; }
    std::string getName() const { return name_; }
    std::string getEmail() const { return email_; }
    
    void setName(const std::string& name) { name_ = name; }
    void setEmail(const std::string& email) { email_ = email; }
};

// User repository interface - 用户仓储接口
class IUserRepository {
public:
    virtual ~IUserRepository() = default;
    virtual std::unique_ptr<User> findById(int id) = 0;
    virtual std::vector<std::unique_ptr<User>> findAll() = 0;
    virtual void save(const User& user) = 0;
    virtual void deleteById(int id) = 0;
};

// ============================================================================
// USE CASES (Application Layer) - 用例层
// ============================================================================

// Create user use case - 创建用户用例
class CreateUserUseCase {
private:
    std::shared_ptr<IUserRepository> userRepository_;

public:
    explicit CreateUserUseCase(std::shared_ptr<IUserRepository> userRepository)
        : userRepository_(userRepository) {}

    std::unique_ptr<User> execute(const std::string& name, const std::string& email) {
        // Business logic validation - 业务逻辑验证
        if (name.empty()) {
            throw std::invalid_argument("Name cannot be empty");
        }
        if (email.empty() || email.find('@') == std::string::npos) {
            throw std::invalid_argument("Invalid email format");
        }

        // Create new user with auto-generated ID
        auto newUser = std::make_unique<User>(generateId(), name, email);
        userRepository_->save(*newUser);
        
        return newUser;
    }

private:
    int generateId() {
        static int nextId = 1;
        return nextId++;
    }
};

// Get user use case - 获取用户用例
class GetUserUseCase {
private:
    std::shared_ptr<IUserRepository> userRepository_;

public:
    explicit GetUserUseCase(std::shared_ptr<IUserRepository> userRepository)
        : userRepository_(userRepository) {}

    std::unique_ptr<User> execute(int id) {
        auto user = userRepository_->findById(id);
        if (!user) {
            throw std::runtime_error("User not found");
        }
        return user;
    }
};

// List users use case - 列出用户用例
class ListUsersUseCase {
private:
    std::shared_ptr<IUserRepository> userRepository_;

public:
    explicit ListUsersUseCase(std::shared_ptr<IUserRepository> userRepository)
        : userRepository_(userRepository) {}

    std::vector<std::unique_ptr<User>> execute() {
        return userRepository_->findAll();
    }
};

// ============================================================================
// INTERFACE ADAPTERS (Infrastructure Layer) - 接口适配层
// ============================================================================

// In-memory user repository implementation - 内存用户仓储实现
class InMemoryUserRepository : public IUserRepository {
private:
    std::vector<std::unique_ptr<User>> users_;

public:
    std::unique_ptr<User> findById(int id) override {
        for (const auto& user : users_) {
            if (user->getId() == id) {
                return std::make_unique<User>(user->getId(), user->getName(), user->getEmail());
            }
        }
        return nullptr;
    }

    std::vector<std::unique_ptr<User>> findAll() override {
        std::vector<std::unique_ptr<User>> result;
        for (const auto& user : users_) {
            result.push_back(std::make_unique<User>(user->getId(), user->getName(), user->getEmail()));
        }
        return result;
    }

    void save(const User& user) override {
        // Check if user already exists
        for (auto& existingUser : users_) {
            if (existingUser->getId() == user.getId()) {
                existingUser->setName(user.getName());
                existingUser->setEmail(user.getEmail());
                return;
            }
        }
        // Add new user
        users_.push_back(std::make_unique<User>(user.getId(), user.getName(), user.getEmail()));
    }

    void deleteById(int id) override {
        users_.erase(
            std::remove_if(users_.begin(), users_.end(),
                [id](const std::unique_ptr<User>& user) { return user->getId() == id; }),
            users_.end()
        );
    }
};

// User presenter interface - 用户展示器接口
class IUserPresenter {
public:
    virtual ~IUserPresenter() = default;
    virtual void presentUser(const User& user) = 0;
    virtual void presentUsers(const std::vector<std::unique_ptr<User>>& users) = 0;
    virtual void presentError(const std::string& error) = 0;
};

// Console user presenter - 控制台用户展示器
class ConsoleUserPresenter : public IUserPresenter {
public:
    void presentUser(const User& user) override {
        std::cout << "User: ID=" << user.getId() 
                  << ", Name=" << user.getName() 
                  << ", Email=" << user.getEmail() << std::endl;
    }

    void presentUsers(const std::vector<std::unique_ptr<User>>& users) override {
        std::cout << "Users (" << users.size() << "):" << std::endl;
        for (const auto& user : users) {
            presentUser(*user);
        }
    }

    void presentError(const std::string& error) override {
        std::cout << "Error: " << error << std::endl;
    }
};

// ============================================================================
// CONTROLLERS (Interface Adapters) - 控制器层
// ============================================================================

// User controller - 用户控制器
class UserController {
private:
    std::shared_ptr<CreateUserUseCase> createUserUseCase_;
    std::shared_ptr<GetUserUseCase> getUserUseCase_;
    std::shared_ptr<ListUsersUseCase> listUsersUseCase_;
    std::shared_ptr<IUserPresenter> presenter_;

public:
    UserController(
        std::shared_ptr<CreateUserUseCase> createUserUseCase,
        std::shared_ptr<GetUserUseCase> getUserUseCase,
        std::shared_ptr<ListUsersUseCase> listUsersUseCase,
        std::shared_ptr<IUserPresenter> presenter)
        : createUserUseCase_(createUserUseCase)
        , getUserUseCase_(getUserUseCase)
        , listUsersUseCase_(listUsersUseCase)
        , presenter_(presenter) {}

    void createUser(const std::string& name, const std::string& email) {
        try {
            auto user = createUserUseCase_->execute(name, email);
            presenter_->presentUser(*user);
        } catch (const std::exception& e) {
            presenter_->presentError(e.what());
        }
    }

    void getUser(int id) {
        try {
            auto user = getUserUseCase_->execute(id);
            presenter_->presentUser(*user);
        } catch (const std::exception& e) {
            presenter_->presentError(e.what());
        }
    }

    void listUsers() {
        try {
            auto users = listUsersUseCase_->execute();
            presenter_->presentUsers(users);
        } catch (const std::exception& e) {
            presenter_->presentError(e.what());
        }
    }
};

// ============================================================================
// MAIN (Frameworks & Drivers) - 主程序层
// ============================================================================

int main() {
    std::cout << "=== Clean Architecture C++11 Example ===" << std::endl;
    std::cout << "=== 清洁架构 C++11 示例 ===" << std::endl << std::endl;

    // Dependency injection setup - 依赖注入设置
    auto userRepository = std::make_shared<InMemoryUserRepository>();
    auto createUserUseCase = std::make_shared<CreateUserUseCase>(userRepository);
    auto getUserUseCase = std::make_shared<GetUserUseCase>(userRepository);
    auto listUsersUseCase = std::make_shared<ListUsersUseCase>(userRepository);
    auto presenter = std::make_shared<ConsoleUserPresenter>();
    
    auto controller = std::make_unique<UserController>(
        createUserUseCase, getUserUseCase, listUsersUseCase, presenter);

    // Demo usage - 演示使用
    std::cout << "Creating users..." << std::endl;
    controller->createUser("Alice", "alice@example.com");
    controller->createUser("Bob", "bob@example.com");
    controller->createUser("Charlie", "charlie@example.com");

    std::cout << "\nListing all users..." << std::endl;
    controller->listUsers();

    std::cout << "\nGetting user by ID..." << std::endl;
    controller->getUser(2);

    std::cout << "\nTrying to get non-existent user..." << std::endl;
    controller->getUser(999);

    std::cout << "\nTrying to create user with invalid data..." << std::endl;
    controller->createUser("", "invalid-email");

    return 0;
} 