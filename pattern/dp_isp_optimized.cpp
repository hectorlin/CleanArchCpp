#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <functional>
#include <type_traits>
#include <numeric>

// Optimized Interface Segregation Principle (ISP) Example
// Using modern C++17/20 features for better performance and type safety

// Bad example: Fat interface forcing clients to depend on methods they don't use
class BadWorker {
public:
    virtual ~BadWorker() = default;
    virtual void work() = 0;
    virtual void eat() = 0;
    virtual void sleep() = 0;
    virtual void getPaid() = 0;
    virtual void takeVacation() = 0;
    virtual void attendMeeting() = 0;
    virtual void writeCode() = 0;
    virtual void designSystem() = 0;
    virtual void manageTeam() = 0;
};

// Bad implementation forcing unused methods
class BadRobot : public BadWorker {
public:
    void work() override { std::cout << "Robot working..." << std::endl; }
    void eat() override { std::cout << "Robot doesn't eat!" << std::endl; } // Unused!
    void sleep() override { std::cout << "Robot doesn't sleep!" << std::endl; } // Unused!
    void getPaid() override { std::cout << "Robot doesn't get paid!" << std::endl; } // Unused!
    void takeVacation() override { std::cout << "Robot doesn't take vacation!" << std::endl; } // Unused!
    void attendMeeting() override { std::cout << "Robot attending meeting..." << std::endl; }
    void writeCode() override { std::cout << "Robot writing code..." << std::endl; }
    void designSystem() override { std::cout << "Robot designing system..." << std::endl; }
    void manageTeam() override { std::cout << "Robot managing team..." << std::endl; }
};

// Optimized example: Segregated interfaces using modern C++ features
// Core work interface
class Workable {
public:
    virtual ~Workable() = default;
    [[nodiscard]] virtual bool canWork() const = 0;
    virtual void work() = 0;
    [[nodiscard]] virtual double getWorkEfficiency() const = 0;
};

// Human-specific interface
class HumanNeeds {
public:
    virtual ~HumanNeeds() = default;
    virtual void eat() = 0;
    virtual void sleep() = 0;
    virtual void takeVacation() = 0;
    [[nodiscard]] virtual bool needsRest() const = 0;
};

// Compensation interface
class Compensable {
public:
    virtual ~Compensable() = default;
    virtual void getPaid() = 0;
    [[nodiscard]] virtual double getSalary() const = 0;
    virtual void requestRaise() = 0;
};

// Communication interface
class Communicative {
public:
    virtual ~Communicative() = default;
    virtual void attendMeeting() = 0;
    virtual void present() = 0;
    [[nodiscard]] virtual bool canCommunicate() const = 0;
};

// Technical work interface
class TechnicalWorker {
public:
    virtual ~TechnicalWorker() = default;
    virtual void writeCode() = 0;
    virtual void debug() = 0;
    virtual void test() = 0;
    [[nodiscard]] virtual std::string getProgrammingLanguage() const = 0;
};

// Design interface
class Designer {
public:
    virtual ~Designer() = default;
    virtual void designSystem() = 0;
    virtual void createPrototype() = 0;
    [[nodiscard]] virtual std::string getDesignTool() const = 0;
};

// Management interface
class Manager {
public:
    virtual ~Manager() = default;
    virtual void manageTeam() = 0;
    virtual void assignTasks() = 0;
    virtual void reviewPerformance() = 0;
    [[nodiscard]] virtual size_t getTeamSize() const = 0;
};

// Optimized concrete implementations
class HumanDeveloper : public Workable, public HumanNeeds, 
                      public Compensable, public Communicative, 
                      public TechnicalWorker {
public:
    HumanDeveloper(std::string name, double salary, std::string language)
        : name_(std::move(name)), salary_(salary), language_(std::move(language)) {}
    
    // Workable implementation
    [[nodiscard]] bool canWork() const override { return !needsRest_; }
    void work() override { 
        std::cout << name_ << " is coding..." << std::endl; 
        needsRest_ = true;
    }
    [[nodiscard]] double getWorkEfficiency() const override { 
        return needsRest_ ? 0.5 : 1.0; 
    }
    
    // HumanNeeds implementation
    void eat() override { 
        std::cout << name_ << " is eating lunch..." << std::endl; 
        needsRest_ = false;
    }
    void sleep() override { 
        std::cout << name_ << " is sleeping..." << std::endl; 
        needsRest_ = false;
    }
    void takeVacation() override { 
        std::cout << name_ << " is on vacation..." << std::endl; 
    }
    [[nodiscard]] bool needsRest() const override { return needsRest_; }
    
    // Compensable implementation
    void getPaid() override { 
        std::cout << name_ << " received $" << salary_ << std::endl; 
    }
    [[nodiscard]] double getSalary() const override { return salary_; }
    void requestRaise() override { 
        std::cout << name_ << " requested a raise" << std::endl; 
    }
    
    // Communicative implementation
    void attendMeeting() override { 
        std::cout << name_ << " is attending a meeting..." << std::endl; 
    }
    void present() override { 
        std::cout << name_ << " is presenting..." << std::endl; 
    }
    [[nodiscard]] bool canCommunicate() const override { return true; }
    
    // TechnicalWorker implementation
    void writeCode() override { 
        std::cout << name_ << " is writing " << language_ << " code..." << std::endl; 
    }
    void debug() override { 
        std::cout << name_ << " is debugging..." << std::endl; 
    }
    void test() override { 
        std::cout << name_ << " is testing..." << std::endl; 
    }
    [[nodiscard]] std::string getProgrammingLanguage() const override { return language_; }

private:
    std::string name_;
    double salary_;
    std::string language_;
    mutable bool needsRest_ = false;
};

class Robot : public Workable, public Communicative, 
             public TechnicalWorker, public Designer {
public:
    explicit Robot(std::string model) : model_(std::move(model)) {}
    
    // Workable implementation
    [[nodiscard]] bool canWork() const override { return true; }
    void work() override { 
        std::cout << model_ << " is working continuously..." << std::endl; 
    }
    [[nodiscard]] double getWorkEfficiency() const override { return 1.0; }
    
    // Communicative implementation
    void attendMeeting() override { 
        std::cout << model_ << " is attending meeting..." << std::endl; 
    }
    void present() override { 
        std::cout << model_ << " is presenting data..." << std::endl; 
    }
    [[nodiscard]] bool canCommunicate() const override { return true; }
    
    // TechnicalWorker implementation
    void writeCode() override { 
        std::cout << model_ << " is writing optimized code..." << std::endl; 
    }
    void debug() override { 
        std::cout << model_ << " is debugging systematically..." << std::endl; 
    }
    void test() override { 
        std::cout << model_ << " is running automated tests..." << std::endl; 
    }
    [[nodiscard]] std::string getProgrammingLanguage() const override { return "C++"; }
    
    // Designer implementation
    void designSystem() override { 
        std::cout << model_ << " is designing system architecture..." << std::endl; 
    }
    void createPrototype() override { 
        std::cout << model_ << " is creating prototype..." << std::endl; 
    }
    [[nodiscard]] std::string getDesignTool() const override { return "AI Design Suite"; }

private:
    std::string model_;
};

// Modern worker manager using segregated interfaces
class WorkerManager {
public:
    // Add workers using modern smart pointers
    void addWorker(std::unique_ptr<Workable> worker) {
        workers_.push_back(std::move(worker));
    }
    
    // Process all workers that can work
    void processWork() const {
        std::for_each(workers_.begin(), workers_.end(),
            [](const auto& worker) {
                if (worker->canWork()) {
                    worker->work();
                }
            });
    }
    
    // Calculate total efficiency
    [[nodiscard]] double getTotalEfficiency() const {
        return std::accumulate(workers_.begin(), workers_.end(), 0.0,
            [](double sum, const auto& worker) { 
                return sum + worker->getWorkEfficiency(); 
            });
    }
    
    // Handle human needs
    void handleHumanNeeds(const std::vector<std::unique_ptr<HumanNeeds>>& humans) {
        std::for_each(humans.begin(), humans.end(),
            [](const auto& human) {
                if (human->needsRest()) {
                    human->sleep();
                }
            });
    }
    
    // Process compensation
    void processCompensation(const std::vector<std::unique_ptr<Compensable>>& employees) {
        std::for_each(employees.begin(), employees.end(),
            [](const auto& employee) { employee->getPaid(); });
    }
    
    // Technical work session
    void technicalWorkSession(const std::vector<std::unique_ptr<TechnicalWorker>>& developers) {
        std::for_each(developers.begin(), developers.end(),
            [](const auto& dev) {
                dev->writeCode();
                dev->test();
                dev->debug();
            });
    }

private:
    std::vector<std::unique_ptr<Workable>> workers_;
};

// Template-based worker factory for compile-time type safety
template<typename WorkerType>
class WorkerFactory {
public:
    template<typename... Args>
    [[nodiscard]] static std::unique_ptr<WorkerType> create(Args&&... args) {
        return std::make_unique<WorkerType>(std::forward<Args>(args)...);
    }
};

int main() {
    std::cout << "=== Optimized Interface Segregation Principle (ISP) Example ===" << std::endl;
    
    // Bad example: Fat interface
    std::cout << "\n--- Bad Example (Fat Interface) ---" << std::endl;
    std::unique_ptr<BadWorker> badRobot = std::make_unique<BadRobot>();
    badRobot->work();
    badRobot->eat(); // Robot forced to implement unused method
    
    // Optimized example: Segregated interfaces
    std::cout << "\n--- Optimized Example (Segregated Interfaces) ---" << std::endl;
    
    WorkerManager manager;
    
    // Create workers with specific interfaces
    auto humanDev = WorkerFactory<HumanDeveloper>::create("Alice", 75000.0, "C++");
    auto robot = WorkerFactory<Robot>::create("RoboDev-3000");
    
    // Add to work manager
    manager.addWorker(std::move(humanDev));
    manager.addWorker(std::move(robot));
    
    // Demonstrate interface segregation
    std::cout << "\nWork session:" << std::endl;
    manager.processWork();
    
    std::cout << "\nTotal efficiency: " << manager.getTotalEfficiency() << std::endl;
    
    // Demonstrate specific interface usage
    auto alice = WorkerFactory<HumanDeveloper>::create("Alice", 75000.0, "C++");
    auto robo = WorkerFactory<Robot>::create("RoboDev-3000");
    
    // Human-specific operations
    std::cout << "\nHuman needs:" << std::endl;
    alice->eat();
    alice->sleep();
    alice->takeVacation();
    
    // Robot-specific operations (no human needs)
    std::cout << "\nRobot capabilities:" << std::endl;
    robo->work();
    robo->writeCode();
    robo->designSystem();
    
    // Compensation (only for humans)
    std::cout << "\nCompensation:" << std::endl;
    alice->getPaid();
    alice->requestRaise();
    
    // Technical work (both can do)
    std::cout << "\nTechnical work:" << std::endl;
    alice->writeCode();
    robo->writeCode();
    
    std::cout << "\nAlice's language: " << alice->getProgrammingLanguage() << std::endl;
    std::cout << "Robot's language: " << robo->getProgrammingLanguage() << std::endl;
    
    return 0;
} 