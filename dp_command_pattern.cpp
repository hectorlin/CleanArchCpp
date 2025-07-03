#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <functional>

// Command Pattern
// Encapsulate a request as an object, allowing parameterization of clients

// Command interface
class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual std::string getDescription() const = 0;
};

// Receiver classes
class Light {
public:
    void turnOn() {
        isOn = true;
        std::cout << "Light is ON" << std::endl;
    }
    
    void turnOff() {
        isOn = false;
        std::cout << "Light is OFF" << std::endl;
    }
    
    bool getState() const { return isOn; }
    
private:
    bool isOn = false;
};

class GarageDoor {
public:
    void open() {
        isOpen = true;
        std::cout << "Garage door is OPEN" << std::endl;
    }
    
    void close() {
        isOpen = false;
        std::cout << "Garage door is CLOSED" << std::endl;
    }
    
    bool getState() const { return isOpen; }
    
private:
    bool isOpen = false;
};

class Stereo {
public:
    void turnOn() {
        isOn = true;
        std::cout << "Stereo is ON" << std::endl;
    }
    
    void turnOff() {
        isOn = false;
        std::cout << "Stereo is OFF" << std::endl;
    }
    
    void setVolume(int volume) {
        this->volume = volume;
        std::cout << "Stereo volume set to " << volume << std::endl;
    }
    
    bool getState() const { return isOn; }
    int getVolume() const { return volume; }
    
private:
    bool isOn = false;
    int volume = 0;
};

// Concrete commands
class LightOnCommand : public Command {
public:
    LightOnCommand(Light* light) : light(light) {}
    
    void execute() override {
        light->turnOn();
    }
    
    void undo() override {
        light->turnOff();
    }
    
    std::string getDescription() const override {
        return "Light On";
    }
    
private:
    Light* light;
};

class LightOffCommand : public Command {
public:
    LightOffCommand(Light* light) : light(light) {}
    
    void execute() override {
        light->turnOff();
    }
    
    void undo() override {
        light->turnOn();
    }
    
    std::string getDescription() const override {
        return "Light Off";
    }
    
private:
    Light* light;
};

class GarageDoorOpenCommand : public Command {
public:
    GarageDoorOpenCommand(GarageDoor* door) : door(door) {}
    
    void execute() override {
        door->open();
    }
    
    void undo() override {
        door->close();
    }
    
    std::string getDescription() const override {
        return "Garage Door Open";
    }
    
private:
    GarageDoor* door;
};

class GarageDoorCloseCommand : public Command {
public:
    GarageDoorCloseCommand(GarageDoor* door) : door(door) {}
    
    void execute() override {
        door->close();
    }
    
    void undo() override {
        door->open();
    }
    
    std::string getDescription() const override {
        return "Garage Door Close";
    }
    
private:
    GarageDoor* door;
};

class StereoOnWithCDCommand : public Command {
public:
    StereoOnWithCDCommand(Stereo* stereo) : stereo(stereo) {}
    
    void execute() override {
        stereo->turnOn();
        stereo->setVolume(11);
        std::cout << "CD is playing" << std::endl;
    }
    
    void undo() override {
        stereo->turnOff();
    }
    
    std::string getDescription() const override {
        return "Stereo On with CD";
    }
    
private:
    Stereo* stereo;
};

// Macro command (composite command)
class MacroCommand : public Command {
public:
    MacroCommand(std::vector<std::shared_ptr<Command>> commands) 
        : commands(std::move(commands)) {}
    
    void execute() override {
        std::cout << "Executing macro command:" << std::endl;
        for (auto& command : commands) {
            command->execute();
        }
    }
    
    void undo() override {
        std::cout << "Undoing macro command:" << std::endl;
        for (auto it = commands.rbegin(); it != commands.rend(); ++it) {
            (*it)->undo();
        }
    }
    
    std::string getDescription() const override {
        return "Macro Command";
    }
    
private:
    std::vector<std::shared_ptr<Command>> commands;
};

// Invoker (Remote Control)
class RemoteControl {
public:
    RemoteControl() {
        onCommands.resize(7);
        offCommands.resize(7);
        
        // Initialize with no-op commands
        for (int i = 0; i < 7; ++i) {
            onCommands[i] = std::make_shared<NoCommand>();
            offCommands[i] = std::make_shared<NoCommand>();
        }
    }
    
    void setCommand(int slot, std::shared_ptr<Command> onCommand, std::shared_ptr<Command> offCommand) {
        onCommands[slot] = std::move(onCommand);
        offCommands[slot] = std::move(offCommand);
    }
    
    void onButtonWasPushed(int slot) {
        onCommands[slot]->execute();
        lastCommand = onCommands[slot];
    }
    
    void offButtonWasPushed(int slot) {
        offCommands[slot]->execute();
        lastCommand = offCommands[slot];
    }
    
    void undoButtonWasPushed() {
        if (lastCommand) {
            lastCommand->undo();
        }
    }
    
    void printStatus() const {
        std::cout << "\n--- Remote Control ---" << std::endl;
        for (int i = 0; i < 7; ++i) {
            std::cout << "slot[" << i << "] " 
                      << onCommands[i]->getDescription() << " "
                      << offCommands[i]->getDescription() << std::endl;
        }
    }
    
private:
    std::vector<std::shared_ptr<Command>> onCommands;
    std::vector<std::shared_ptr<Command>> offCommands;
    std::shared_ptr<Command> lastCommand;
};

// No-op command (null object pattern)
class NoCommand : public Command {
public:
    void execute() override {
        // Do nothing
    }
    
    void undo() override {
        // Do nothing
    }
    
    std::string getDescription() const override {
        return "No Command";
    }
};

// Lambda-based command (modern C++ approach)
class LambdaCommand : public Command {
public:
    LambdaCommand(std::function<void()> executeFunc, 
                  std::function<void()> undoFunc,
                  const std::string& description)
        : executeFunc(std::move(executeFunc))
        , undoFunc(std::move(undoFunc))
        , description(description) {}
    
    void execute() override {
        executeFunc();
    }
    
    void undo() override {
        undoFunc();
    }
    
    std::string getDescription() const override {
        return description;
    }
    
private:
    std::function<void()> executeFunc;
    std::function<void()> undoFunc;
    std::string description;
};

int main() {
    std::cout << "=== Command Pattern Example ===" << std::endl;
    
    // Create receivers
    Light livingRoomLight;
    Light kitchenLight;
    GarageDoor garageDoor;
    Stereo stereo;
    
    // Create commands
    auto livingRoomLightOn = std::make_shared<LightOnCommand>(&livingRoomLight);
    auto livingRoomLightOff = std::make_shared<LightOffCommand>(&livingRoomLight);
    auto kitchenLightOn = std::make_shared<LightOnCommand>(&kitchenLight);
    auto kitchenLightOff = std::make_shared<LightOffCommand>(&kitchenLight);
    auto garageDoorOpen = std::make_shared<GarageDoorOpenCommand>(&garageDoor);
    auto garageDoorClose = std::make_shared<GarageDoorCloseCommand>(&garageDoor);
    auto stereoOnWithCD = std::make_shared<StereoOnWithCDCommand>(&stereo);
    
    // Create remote control
    RemoteControl remote;
    
    // Set commands
    remote.setCommand(0, livingRoomLightOn, livingRoomLightOff);
    remote.setCommand(1, kitchenLightOn, kitchenLightOff);
    remote.setCommand(2, garageDoorOpen, garageDoorClose);
    remote.setCommand(3, stereoOnWithCD, std::make_shared<NoCommand>());
    
    // Create macro command
    std::vector<std::shared_ptr<Command>> partyOn = {
        livingRoomLightOn,
        kitchenLightOn,
        stereoOnWithCD
    };
    
    std::vector<std::shared_ptr<Command>> partyOff = {
        livingRoomLightOff,
        kitchenLightOff,
        std::make_shared<LambdaCommand>(
            [&stereo]() { stereo.turnOff(); },
            [&stereo]() { stereo.turnOn(); },
            "Stereo Off"
        )
    };
    
    auto partyOnMacro = std::make_shared<MacroCommand>(partyOn);
    auto partyOffMacro = std::make_shared<MacroCommand>(partyOff);
    
    remote.setCommand(4, partyOnMacro, partyOffMacro);
    
    // Print remote status
    remote.printStatus();
    
    // Test commands
    std::cout << "\n--- Testing Commands ---" << std::endl;
    
    remote.onButtonWasPushed(0);  // Living room light on
    remote.onButtonWasPushed(1);  // Kitchen light on
    remote.offButtonWasPushed(0); // Living room light off
    remote.onButtonWasPushed(2);  // Garage door open
    remote.onButtonWasPushed(3);  // Stereo on with CD
    
    // Test undo
    std::cout << "\n--- Testing Undo ---" << std::endl;
    remote.undoButtonWasPushed(); // Undo stereo
    remote.undoButtonWasPushed(); // Undo garage door
    
    // Test macro command
    std::cout << "\n--- Testing Macro Command ---" << std::endl;
    remote.onButtonWasPushed(4);  // Party on
    remote.offButtonWasPushed(4); // Party off
    
    return 0;
} 