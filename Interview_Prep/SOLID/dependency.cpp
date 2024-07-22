#include <iostream>
#include <memory>

// Dependency Inversion Principle (DIP)

// Definition: High-level modules should not depend on low-level modules. Both should depend 
// on abstractions. Abstractions should not depend on details. Details should depend on 
// abstractions.

// Explanation: This principle aims to reduce the coupling between high-level and 
// low-level modules by introducing an abstraction layer. This makes the system more 
// flexible and easier to maintain.

// Before DIP: High-level module depends on low-level module
class LightBulb {
public:
    void turnOn() {
        std::cout << "LightBulb is on" << std::endl;
    }

    void turnOff() {
        std::cout << "LightBulb is off" << std::endl;
    }
};

class Switch {
public:
    void operate() {
        bulb.turnOn();
    }

private:
    LightBulb bulb;
};

// After DIP: High-level module depends on an abstraction
class Switchable {
public:
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
};

class LightBulb : public Switchable {
public:
    void turnOn() override {
        std::cout << "LightBulb is on" << std::endl;
    }

    void turnOff() override {
        std::cout << "LightBulb is off" << std::endl;
    }
};

class Switch {
public:
    Switch(std::shared_ptr<Switchable> device) : device(device) {}

    void operate() {
        device->turnOn();
    }

private:
    std::shared_ptr<Switchable> device;
};

int main() {
    std::shared_ptr<Switchable> bulb = std::make_shared<LightBulb>();
    Switch lightSwitch(bulb);
    lightSwitch.operate();

    return 0;
}