#include <iostream>

// Dynamic Cast
// dynamic_cast is used for safe downcasting in inheritance hierarchis. It performs a runtime check to ensure that the downcast is valid.
// If the cast is invalid, it returns nullptr for pointers or throws a std::bad_cast exception for references.

// Use dynamic_cast for safe downcasting: It ensures that the cast is valid at runtime.

// dynamic_cast | Safe downcasting | Runtime checks

class Base{
    public:
    virtual void print() { std::cout << "Base::print" << std::endl; }
};

class Derived : public Base{
    public:
    void print() override { std::cout << "Derived::print" << std::endl; }
};

int main() {
    Base * basePtr = new Derived();
    Derived *derivedPtr = dynamic_cast<Derived *>(basePtr); // Safe downcating

    if (derivedPtr) {
        basePtr->print();
    } else {
        std::cout << "Downcast failed" << std::endl;
    }

    delete basePtr;
    return 0;
}