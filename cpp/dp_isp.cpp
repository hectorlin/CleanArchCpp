#include <iostream>
#include <string>

// Interface Segregation Principle (ISP)
// Clients should not be forced to depend on interfaces they do not use

// Bad example: Fat interface that forces clients to implement unused methods
class BadWorker {
public:
    virtual void work() = 0;
    virtual void eat() = 0;
    virtual void sleep() = 0;
    virtual void getSalary() = 0;
    virtual void takeVacation() = 0;
    virtual void attendMeeting() = 0;
    virtual void writeCode() = 0;
    virtual void designSystem() = 0;
    virtual void manageTeam() = 0;
};

// Good example: Segregated interfaces
class Workable {
public:
    virtual ~Workable() = default;
    virtual void work() = 0;
};

class Eatable {
public:
    virtual ~Eatable() = default;
    virtual void eat() = 0;
};

class Sleepable {
public:
    virtual ~Sleepable() = default;
    virtual void sleep() = 0;
};

class Payable {
public:
    virtual ~Payable() = default;
    virtual void getSalary() = 0;
};

class Vacationable {
public:
    virtual ~Vacationable() = default;
    virtual void takeVacation() = 0;
};

class MeetingAttendable {
public:
    virtual ~MeetingAttendable() = default;
    virtual void attendMeeting() = 0;
};

class Codable {
public:
    virtual ~Codable() = default;
    virtual void writeCode() = 0;
};

class Designable {
public:
    virtual ~Designable() = default;
    virtual void designSystem() = 0;
};

class Manageable {
public:
    virtual ~Manageable() = default;
    virtual void manageTeam() = 0;
};

// Concrete classes implementing only the interfaces they need
class Human : public Workable, public Eatable, public Sleepable, public Payable, public Vacationable {
public:
    void work() override { std::cout << "Human is working" << std::endl; }
    void eat() override { std::cout << "Human is eating" << std::endl; }
    void sleep() override { std::cout << "Human is sleeping" << std::endl; }
    void getSalary() override { std::cout << "Human gets salary" << std::endl; }
    void takeVacation() override { std::cout << "Human takes vacation" << std::endl; }
};

class Robot : public Workable, public Codable {
public:
    void work() override { std::cout << "Robot is working" << std::endl; }
    void writeCode() override { std::cout << "Robot is writing code" << std::endl; }
};

class Manager : public Human, public Manageable, public MeetingAttendable {
public:
    void manageTeam() override { std::cout << "Manager is managing team" << std::endl; }
    void attendMeeting() override { std::cout << "Manager is attending meeting" << std::endl; }
};

class Designer : public Human, public Designable {
public:
    void designSystem() override { std::cout << "Designer is designing system" << std::endl; }
};

int main() {
    std::cout << "=== Interface Segregation Principle (ISP) Example ===" << std::endl;
    
    // Bad example: Robot forced to implement human methods
    std::cout << "\n--- Bad Example (Fat Interface) ---" << std::endl;
    std::cout << "Robot would be forced to implement eat(), sleep(), etc." << std::endl;
    
    // Good example: Segregated interfaces
    std::cout << "\n--- Good Example (Segregated Interfaces) ---" << std::endl;
    
    Human human;
    Robot robot;
    Manager manager;
    Designer designer;
    
    std::cout << "Human activities:" << std::endl;
    human.work();
    human.eat();
    human.sleep();
    human.getSalary();
    human.takeVacation();
    
    std::cout << "\nRobot activities:" << std::endl;
    robot.work();
    robot.writeCode();
    
    std::cout << "\nManager activities:" << std::endl;
    manager.work();
    manager.manageTeam();
    manager.attendMeeting();
    
    std::cout << "\nDesigner activities:" << std::endl;
    designer.work();
    designer.designSystem();
    
    return 0;
} 