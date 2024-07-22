#include <iostream>

// Liskov Substitution Principle (LSP)

// Definition: Objects of a superclass should be replaceable with objects of a subclass 
// without affecting the correctness of the program.

// Explanation: Subtypes must be substitutable for their base types. 
// This means that derived classes should extend the base class without changing its behavior. 
// Violating this principle can lead to unexpected behavior and bugs.

class Bird {
public:
    virtual void fly() {
        std::cout << "Bird is flying" << std::endl;
    }
};

class Sparrow : public Bird {
public:
    void fly() override {
        std::cout << "Sparrow is flying" << std::endl;
    }
};

// Violation of LSP: Penguin cannot fly
class Penguin : public Bird {
public:
    void fly() override {
        throw std::logic_error("Penguins can't fly");
    }
};