#include <iostream>
#include <memory>
#include <vector>
#include <functional>
#include <string>
#include <queue>
#include <stack>

// Optimized Command Pattern Example
// Using modern C++17/20 features for better performance and type safety

// Bad example: Direct method calls without abstraction
class BadCalculator {
public:
    void add(int value) {
        result_ += value;
        std::cout << "Added " << value << ", result: " << result_ << std::endl;
    }
    
    void subtract(int value) {
        result_ -= value;
        std::cout << "Subtracted " << value << ", result: " << result_ << std::endl;
    }
    
    void multiply(int value) {
        result_ *= value;
        std::cout << "Multiplied by " << value << ", result: " << result_ << std::endl;
    }
    
    void divide(int value) {
        if (value != 0) {
            result_ /= value;
            std::cout << "Divided by " << value << ", result: " << result_ << std::endl;
        } else {
            std::cout << "Cannot divide by zero!" << std::endl;
        }
    }
    
    [[nodiscard]] int getResult() const {
        return result_;
    }

private:
    int result_ = 0;
};

// Optimized example: Command pattern with modern C++ features

// Modern command interface using std::function
class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
    [[nodiscard]] virtual std::string getDescription() const = 0;
};

// Modern calculator with command pattern
class ModernCalculator {
public:
    void add(int value) {
        result_ += value;
        std::cout << "Added " << value << ", result: " << result_ << std::endl;
    }
    
    void subtract(int value) {
        result_ -= value;
        std::cout << "Subtracted " << value << ", result: " << result_ << std::endl;
    }
    
    void multiply(int value) {
        result_ *= value;
        std::cout << "Multiplied by " << value << ", result: " << result_ << std::endl;
    }
    
    void divide(int value) {
        if (value != 0) {
            result_ /= value;
            std::cout << "Divided by " << value << ", result: " << result_ << std::endl;
        } else {
            std::cout << "Cannot divide by zero!" << std::endl;
        }
    }
    
    void setResult(int result) {
        result_ = result;
    }
    
    [[nodiscard]] int getResult() const {
        return result_;
    }

private:
    int result_ = 0;
};

// Concrete command classes
class AddCommand : public Command {
public:
    AddCommand(ModernCalculator& calc, int value) : calculator_(calc), value_(value) {}
    
    void execute() override {
        previousResult_ = calculator_.getResult();
        calculator_.add(value_);
    }
    
    void undo() override {
        calculator_.setResult(previousResult_);
        std::cout << "Undid add " << value_ << ", result: " << calculator_.getResult() << std::endl;
    }
    
    [[nodiscard]] std::string getDescription() const override {
        return "Add " + std::to_string(value_);
    }

private:
    ModernCalculator& calculator_;
    int value_;
    int previousResult_ = 0;
};

class SubtractCommand : public Command {
public:
    SubtractCommand(ModernCalculator& calc, int value) : calculator_(calc), value_(value) {}
    
    void execute() override {
        previousResult_ = calculator_.getResult();
        calculator_.subtract(value_);
    }
    
    void undo() override {
        calculator_.setResult(previousResult_);
        std::cout << "Undid subtract " << value_ << ", result: " << calculator_.getResult() << std::endl;
    }
    
    [[nodiscard]] std::string getDescription() const override {
        return "Subtract " + std::to_string(value_);
    }

private:
    ModernCalculator& calculator_;
    int value_;
    int previousResult_ = 0;
};

class MultiplyCommand : public Command {
public:
    MultiplyCommand(ModernCalculator& calc, int value) : calculator_(calc), value_(value) {}
    
    void execute() override {
        previousResult_ = calculator_.getResult();
        calculator_.multiply(value_);
    }
    
    void undo() override {
        calculator_.setResult(previousResult_);
        std::cout << "Undid multiply by " << value_ << ", result: " << calculator_.getResult() << std::endl;
    }
    
    [[nodiscard]] std::string getDescription() const override {
        return "Multiply by " + std::to_string(value_);
    }

private:
    ModernCalculator& calculator_;
    int value_;
    int previousResult_ = 0;
};

class DivideCommand : public Command {
public:
    DivideCommand(ModernCalculator& calc, int value) : calculator_(calc), value_(value) {}
    
    void execute() override {
        previousResult_ = calculator_.getResult();
        if (value_ != 0) {
            calculator_.divide(value_);
        } else {
            std::cout << "Cannot divide by zero!" << std::endl;
        }
    }
    
    void undo() override {
        calculator_.setResult(previousResult_);
        std::cout << "Undid divide by " << value_ << ", result: " << calculator_.getResult() << std::endl;
    }
    
    [[nodiscard]] std::string getDescription() const override {
        return "Divide by " + std::to_string(value_);
    }

private:
    ModernCalculator& calculator_;
    int value_;
    int previousResult_ = 0;
};

// Modern command invoker with undo/redo functionality
class CommandInvoker {
public:
    void executeCommand(std::unique_ptr<Command> command) {
        command->execute();
        undoStack_.push(std::move(command));
        redoStack_.clear(); // Clear redo stack when new command is executed
    }
    
    void undo() {
        if (!undoStack_.empty()) {
            auto command = std::move(undoStack_.top());
            undoStack_.pop();
            command->undo();
            redoStack_.push(std::move(command));
        } else {
            std::cout << "Nothing to undo!" << std::endl;
        }
    }
    
    void redo() {
        if (!redoStack_.empty()) {
            auto command = std::move(redoStack_.top());
            redoStack_.pop();
            command->execute();
            undoStack_.push(std::move(command));
        } else {
            std::cout << "Nothing to redo!" << std::endl;
        }
    }
    
    [[nodiscard]] bool canUndo() const {
        return !undoStack_.empty();
    }
    
    [[nodiscard]] bool canRedo() const {
        return !redoStack_.empty();
    }
    
    void clearHistory() {
        while (!undoStack_.empty()) undoStack_.pop();
        while (!redoStack_.empty()) redoStack_.pop();
    }

private:
    std::stack<std::unique_ptr<Command>> undoStack_;
    std::stack<std::unique_ptr<Command>> redoStack_;
};

// Modern command using std::function
class FunctionalCommand {
public:
    using ExecuteFunc = std::function<void()>;
    using UndoFunc = std::function<void()>;
    
    FunctionalCommand(ExecuteFunc execute, UndoFunc undo, std::string description)
        : execute_(std::move(execute))
        , undo_(std::move(undo))
        , description_(std::move(description)) {}
    
    void execute() {
        if (execute_) execute_();
    }
    
    void undo() {
        if (undo_) undo_();
    }
    
    [[nodiscard]] const std::string& getDescription() const {
        return description_;
    }

private:
    ExecuteFunc execute_;
    UndoFunc undo_;
    std::string description_;
};

// Modern command factory
class CommandFactory {
public:
    static std::unique_ptr<Command> createAddCommand(ModernCalculator& calc, int value) {
        return std::make_unique<AddCommand>(calc, value);
    }
    
    static std::unique_ptr<Command> createSubtractCommand(ModernCalculator& calc, int value) {
        return std::make_unique<SubtractCommand>(calc, value);
    }
    
    static std::unique_ptr<Command> createMultiplyCommand(ModernCalculator& calc, int value) {
        return std::make_unique<MultiplyCommand>(calc, value);
    }
    
    static std::unique_ptr<Command> createDivideCommand(ModernCalculator& calc, int value) {
        return std::make_unique<DivideCommand>(calc, value);
    }
    
    // Template factory for any command type
    template<typename CommandType, typename... Args>
    static std::unique_ptr<Command> create(Args&&... args) {
        return std::make_unique<CommandType>(std::forward<Args>(args)...);
    }
};

// Modern command queue for batch processing
class CommandQueue {
public:
    void addCommand(std::unique_ptr<Command> command) {
        queue_.push(std::move(command));
    }
    
    void executeAll() {
        while (!queue_.empty()) {
            auto command = std::move(queue_.front());
            queue_.pop();
            command->execute();
        }
    }
    
    [[nodiscard]] size_t size() const {
        return queue_.size();
    }
    
    void clear() {
        while (!queue_.empty()) queue_.pop();
    }

private:
    std::queue<std::unique_ptr<Command>> queue_;
};

// Modern macro command (composite command)
class MacroCommand : public Command {
public:
    void addCommand(std::unique_ptr<Command> command) {
        commands_.push_back(std::move(command));
    }
    
    void execute() override {
        for (const auto& command : commands_) {
            command->execute();
        }
    }
    
    void undo() override {
        // Undo in reverse order
        for (auto it = commands_.rbegin(); it != commands_.rend(); ++it) {
            (*it)->undo();
        }
    }
    
    [[nodiscard]] std::string getDescription() const override {
        std::string desc = "Macro Command (";
        for (size_t i = 0; i < commands_.size(); ++i) {
            if (i > 0) desc += ", ";
            desc += commands_[i]->getDescription();
        }
        desc += ")";
        return desc;
    }
    
    [[nodiscard]] size_t size() const {
        return commands_.size();
    }

private:
    std::vector<std::unique_ptr<Command>> commands_;
};

// Modern command with state tracking
class StatefulCommand : public Command {
public:
    StatefulCommand(ModernCalculator& calc, int value, std::string operation)
        : calculator_(calc), value_(value), operation_(std::move(operation)) {}
    
    void execute() override {
        previousResult_ = calculator_.getResult();
        if (operation_ == "add") {
            calculator_.add(value_);
        } else if (operation_ == "subtract") {
            calculator_.subtract(value_);
        } else if (operation_ == "multiply") {
            calculator_.multiply(value_);
        } else if (operation_ == "divide") {
            calculator_.divide(value_);
        }
    }
    
    void undo() override {
        calculator_.setResult(previousResult_);
        std::cout << "Undid " << operation_ << " " << value_ << std::endl;
    }
    
    [[nodiscard]] std::string getDescription() const override {
        return operation_ + " " + std::to_string(value_);
    }

private:
    ModernCalculator& calculator_;
    int value_;
    std::string operation_;
    int previousResult_ = 0;
};

int main() {
    std::cout << "=== Optimized Command Pattern Example ===" << std::endl;
    
    // Bad example: Direct method calls
    std::cout << "\n--- Bad Example (Direct Method Calls) ---" << std::endl;
    BadCalculator badCalc;
    badCalc.add(5);
    badCalc.multiply(3);
    badCalc.subtract(2);
    std::cout << "Final result: " << badCalc.getResult() << std::endl;
    
    // Optimized example: Command pattern
    std::cout << "\n--- Optimized Example (Command Pattern) ---" << std::endl;
    
    ModernCalculator calc;
    CommandInvoker invoker;
    
    // Execute commands
    invoker.executeCommand(CommandFactory::createAddCommand(calc, 5));
    invoker.executeCommand(CommandFactory::createMultiplyCommand(calc, 3));
    invoker.executeCommand(CommandFactory::createSubtractCommand(calc, 2));
    
    std::cout << "Final result: " << calc.getResult() << std::endl;
    
    // Demonstrate undo/redo
    std::cout << "\n--- Undo/Redo Demo ---" << std::endl;
    
    invoker.undo(); // Undo subtract
    std::cout << "After undo: " << calc.getResult() << std::endl;
    
    invoker.undo(); // Undo multiply
    std::cout << "After second undo: " << calc.getResult() << std::endl;
    
    invoker.redo(); // Redo multiply
    std::cout << "After redo: " << calc.getResult() << std::endl;
    
    // Command queue example
    std::cout << "\n--- Command Queue Example ---" << std::endl;
    
    CommandQueue queue;
    ModernCalculator queueCalc;
    
    queue.addCommand(CommandFactory::createAddCommand(queueCalc, 10));
    queue.addCommand(CommandFactory::createMultiplyCommand(queueCalc, 2));
    queue.addCommand(CommandFactory::createSubtractCommand(queueCalc, 5));
    
    std::cout << "Queue size: " << queue.size() << std::endl;
    queue.executeAll();
    std::cout << "Queue result: " << queueCalc.getResult() << std::endl;
    
    // Macro command example
    std::cout << "\n--- Macro Command Example ---" << std::endl;
    
    ModernCalculator macroCalc;
    auto macro = std::make_unique<MacroCommand>();
    
    macro->addCommand(CommandFactory::createAddCommand(macroCalc, 5));
    macro->addCommand(CommandFactory::createMultiplyCommand(macroCalc, 2));
    macro->addCommand(CommandFactory::createAddCommand(macroCalc, 10));
    
    std::cout << "Macro description: " << macro->getDescription() << std::endl;
    macro->execute();
    std::cout << "Macro result: " << macroCalc.getResult() << std::endl;
    
    macro->undo();
    std::cout << "After macro undo: " << macroCalc.getResult() << std::endl;
    
    // Functional command example
    std::cout << "\n--- Functional Command Example ---" << std::endl;
    
    ModernCalculator funcCalc;
    
    auto addFunc = [&funcCalc](int value) {
        return FunctionalCommand(
            [&funcCalc, value]() { funcCalc.add(value); },
            [&funcCalc, value]() { funcCalc.subtract(value); },
            "Add " + std::to_string(value)
        );
    };
    
    auto addCommand = addFunc(7);
    addCommand.execute();
    std::cout << "Functional command result: " << funcCalc.getResult() << std::endl;
    addCommand.undo();
    std::cout << "After functional undo: " << funcCalc.getResult() << std::endl;
    
    return 0;
} 