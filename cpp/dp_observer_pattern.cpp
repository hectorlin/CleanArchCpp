#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <functional>

// Observer Pattern
// Define a one-to-many dependency between objects so that when one object changes state,
// all its dependents are notified and updated automatically

// Observer interface
class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(const std::string& message) = 0;
    virtual std::string getName() const = 0;
};

// Subject interface
class Subject {
public:
    virtual ~Subject() = default;
    virtual void attach(std::shared_ptr<Observer> observer) = 0;
    virtual void detach(std::shared_ptr<Observer> observer) = 0;
    virtual void notify(const std::string& message) = 0;
};

// Concrete Subject: Weather Station
class WeatherStation : public Subject {
public:
    void attach(std::shared_ptr<Observer> observer) override {
        observers.push_back(observer);
        std::cout << "Observer " << observer->getName() << " attached" << std::endl;
    }
    
    void detach(std::shared_ptr<Observer> observer) override {
        auto it = std::find(observers.begin(), observers.end(), observer);
        if (it != observers.end()) {
            observers.erase(it);
            std::cout << "Observer " << observer->getName() << " detached" << std::endl;
        }
    }
    
    void notify(const std::string& message) override {
        std::cout << "Weather Station: Notifying " << observers.size() << " observers" << std::endl;
        for (auto& observer : observers) {
            observer->update(message);
        }
    }
    
    void setMeasurements(float temperature, float humidity, float pressure) {
        this->temperature = temperature;
        this->humidity = humidity;
        this->pressure = pressure;
        
        std::string message = "Temperature: " + std::to_string(temperature) + 
                             "°C, Humidity: " + std::to_string(humidity) + 
                             "%, Pressure: " + std::to_string(pressure) + " hPa";
        notify(message);
    }
    
    float getTemperature() const { return temperature; }
    float getHumidity() const { return humidity; }
    float getPressure() const { return pressure; }
    
private:
    std::vector<std::shared_ptr<Observer>> observers;
    float temperature = 0.0f;
    float humidity = 0.0f;
    float pressure = 0.0f;
};

// Concrete Observers
class CurrentConditionsDisplay : public Observer {
public:
    CurrentConditionsDisplay(const std::string& name) : name(name) {}
    
    void update(const std::string& message) override {
        std::cout << "[" << name << "] Current conditions: " << message << std::endl;
    }
    
    std::string getName() const override {
        return name;
    }
    
private:
    std::string name;
};

class StatisticsDisplay : public Observer {
public:
    StatisticsDisplay(const std::string& name) : name(name) {}
    
    void update(const std::string& message) override {
        std::cout << "[" << name << "] Statistics updated: " << message << std::endl;
        // In a real implementation, this would calculate and store statistics
    }
    
    std::string getName() const override {
        return name;
    }
    
private:
    std::string name;
};

class ForecastDisplay : public Observer {
public:
    ForecastDisplay(const std::string& name) : name(name) {}
    
    void update(const std::string& message) override {
        std::cout << "[" << name << "] Forecast updated: " << message << std::endl;
        // In a real implementation, this would generate weather forecasts
    }
    
    std::string getName() const override {
        return name;
    }
    
private:
    std::string name;
};

// Modern Observer using std::function (C++11 approach)
class ModernSubject {
public:
    using ObserverCallback = std::function<void(const std::string&)>;
    
    void attach(const std::string& name, ObserverCallback callback) {
        observers[name] = std::move(callback);
        std::cout << "Observer " << name << " attached (modern)" << std::endl;
    }
    
    void detach(const std::string& name) {
        if (observers.erase(name) > 0) {
            std::cout << "Observer " << name << " detached (modern)" << std::endl;
        }
    }
    
    void notify(const std::string& message) {
        std::cout << "Modern Subject: Notifying " << observers.size() << " observers" << std::endl;
        for (auto& [name, callback] : observers) {
            callback(message);
        }
    }
    
    void setData(const std::string& data) {
        this->data = data;
        notify("Data changed to: " + data);
    }
    
private:
    std::map<std::string, ObserverCallback> observers;
    std::string data;
};

// Event-driven Observer Pattern
class Event {
public:
    Event(const std::string& type, const std::string& data) 
        : type(type), data(data), timestamp(std::time(nullptr)) {}
    
    std::string getType() const { return type; }
    std::string getData() const { return data; }
    std::time_t getTimestamp() const { return timestamp; }
    
private:
    std::string type;
    std::string data;
    std::time_t timestamp;
};

class EventObserver {
public:
    virtual ~EventObserver() = default;
    virtual void onEvent(const Event& event) = 0;
    virtual std::string getName() const = 0;
};

class EventSubject {
public:
    void subscribe(const std::string& eventType, std::shared_ptr<EventObserver> observer) {
        subscribers[eventType].push_back(observer);
        std::cout << "Observer " << observer->getName() << " subscribed to " << eventType << std::endl;
    }
    
    void unsubscribe(const std::string& eventType, std::shared_ptr<EventObserver> observer) {
        auto& eventSubscribers = subscribers[eventType];
        auto it = std::find(eventSubscribers.begin(), eventSubscribers.end(), observer);
        if (it != eventSubscribers.end()) {
            eventSubscribers.erase(it);
            std::cout << "Observer " << observer->getName() << " unsubscribed from " << eventType << std::endl;
        }
    }
    
    void publish(const Event& event) {
        auto it = subscribers.find(event.getType());
        if (it != subscribers.end()) {
            std::cout << "Publishing event: " << event.getType() << " to " << it->second.size() << " subscribers" << std::endl;
            for (auto& observer : it->second) {
                observer->onEvent(event);
            }
        }
    }
    
private:
    std::map<std::string, std::vector<std::shared_ptr<EventObserver>>> subscribers;
};

class LoggingObserver : public EventObserver {
public:
    LoggingObserver(const std::string& name) : name(name) {}
    
    void onEvent(const Event& event) override {
        std::cout << "[" << name << "] Logging event: " << event.getType() 
                  << " - " << event.getData() << std::endl;
    }
    
    std::string getName() const override {
        return name;
    }
    
private:
    std::string name;
};

class AlertingObserver : public EventObserver {
public:
    AlertingObserver(const std::string& name) : name(name) {}
    
    void onEvent(const Event& event) override {
        if (event.getType() == "ERROR") {
            std::cout << "[" << name << "] ALERT: " << event.getData() << std::endl;
        }
    }
    
    std::string getName() const override {
        return name;
    }
    
private:
    std::string name;
};

int main() {
    std::cout << "=== Observer Pattern Example ===" << std::endl;
    
    // Traditional Observer Pattern
    std::cout << "\n--- Traditional Observer Pattern ---" << std::endl;
    
    auto weatherStation = std::make_shared<WeatherStation>();
    
    auto currentDisplay = std::make_shared<CurrentConditionsDisplay>("Current Display");
    auto statisticsDisplay = std::make_shared<StatisticsDisplay>("Statistics Display");
    auto forecastDisplay = std::make_shared<ForecastDisplay>("Forecast Display");
    
    weatherStation->attach(currentDisplay);
    weatherStation->attach(statisticsDisplay);
    weatherStation->attach(forecastDisplay);
    
    weatherStation->setMeasurements(25.5f, 65.0f, 1013.25f);
    weatherStation->setMeasurements(26.2f, 70.0f, 1012.50f);
    
    weatherStation->detach(statisticsDisplay);
    weatherStation->setMeasurements(24.8f, 60.0f, 1014.00f);
    
    // Modern Observer Pattern with std::function
    std::cout << "\n--- Modern Observer Pattern ---" << std::endl;
    
    ModernSubject modernSubject;
    
    modernSubject.attach("Logger", [](const std::string& msg) {
        std::cout << "[Logger] " << msg << std::endl;
    });
    
    modernSubject.attach("Monitor", [](const std::string& msg) {
        std::cout << "[Monitor] " << msg << std::endl;
    });
    
    modernSubject.setData("Initial data");
    modernSubject.setData("Updated data");
    
    modernSubject.detach("Logger");
    modernSubject.setData("Data after logger detached");
    
    // Event-driven Observer Pattern
    std::cout << "\n--- Event-driven Observer Pattern ---" << std::endl;
    
    EventSubject eventSubject;
    
    auto loggingObserver = std::make_shared<LoggingObserver>("System Logger");
    auto alertingObserver = std::make_shared<AlertingObserver>("Alert System");
    
    eventSubject.subscribe("INFO", loggingObserver);
    eventSubject.subscribe("ERROR", loggingObserver);
    eventSubject.subscribe("ERROR", alertingObserver);
    eventSubject.subscribe("WARNING", loggingObserver);
    
    eventSubject.publish(Event("INFO", "System started successfully"));
    eventSubject.publish(Event("WARNING", "High memory usage detected"));
    eventSubject.publish(Event("ERROR", "Database connection failed"));
    
    eventSubject.unsubscribe("ERROR", alertingObserver);
    eventSubject.publish(Event("ERROR", "Another error occurred"));
    
    return 0;
} 