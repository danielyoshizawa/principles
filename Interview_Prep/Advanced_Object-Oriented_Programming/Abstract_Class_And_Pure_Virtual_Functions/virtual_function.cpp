#include <iostream>

// Virtual Function:
// A virtual function is a member function in a base class that you expect to override in 
// derived classes. It allows derived classes to provide specific implementations while 
// enabling runtime polymorphism.

// Characteristics:
// 1. Can Have Implementation: A virtual function can have a default implementation in the base class.
// 2. Can Be Overridden: Derived classes can override the virtual function.
// 3. Can Be Used to Enable Runtime Polymorphism: Allows derived classes to provide specific 
// implementations while enabling runtime polymorphism.

class Base {
    public:
        virtual void print() { // Default implementation
            std::cout << "Base" << std::endl;
        }

        virtual void printBase() {
            std::cout << "Calling Base" << std::endl;
        }
};

class Derived : public Base {
    public:
        void print() override { // Overriding the default implementation
            std::cout << "Derived" << std::endl;
        }

        void printBase() override {
            Base::printBase();
            std::cout << "From Derived" << std::endl;
        }
};

class Other : public Base{
    public:
        void print() override { // Overriding the default implementation
            std::cout << "Other" << std::endl;
        }

        void printBase() override {
            Base::printBase();
            std::cout << "From Other" << std::endl;
        }
};

int main() {
    Base* base = new Derived();
    base->print();
    base->printBase();
    delete base;
    base = new Other();
    base->print();
    base->printBase();

    return 0;
}