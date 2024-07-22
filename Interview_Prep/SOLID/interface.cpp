#include <iostream>

// Interface Segregation Principle (ISP)

// Definition: Clients should not be forced to depend on interfaces they do not use.


// Explanation: Instead of having one large interface, create smaller, 
// more specific interfaces so that clients only need to know about the methods 
// that are of interest to them. This helps in reducing the impact of changes and 
// makes the code more modular.

// Before ISP: A large interface with unrelated methods
class IWorker {
public:
    virtual void work() = 0;
    virtual void eat() = 0;
};

// After ISP: Smaller, more specific interfaces
class IWorkable {
public:
    virtual void work() = 0;
};

class IFeedable {
public:
    virtual void eat() = 0;
};

class Worker : public IWorkable, public IFeedable {
public:
    void work() override {
        std::cout << "Working" << std::endl;
    }

    void eat() override {
        std::cout << "Eating" << std::endl;
    }
};