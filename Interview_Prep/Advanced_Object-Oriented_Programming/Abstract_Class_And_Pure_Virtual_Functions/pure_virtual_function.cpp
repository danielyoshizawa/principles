#include <iostream>

// Pure Virtual Function

// A pure virtual function is a virtual function that has no implementation in the base class and 
// must be overridden in any derived class. Declaring a pure virtual function makes the 
// class abstract, meaning it cannot be instantiated.

// Characteristis:
// 1. No Implementation: A pure virtual function has no implementation in the base class.
// 2. Must Be Overridden: Derived classes must override the pure virtual function.
// 3. Abstract Class: Declaring a pure virtual function makes the class abstract, meaning it cannot be instantiated.

class PureVirtual {
    public:
        virtual void print() = 0; // Pure virtual function
};

class Impl : public PureVirtual {
    public:
        void print() override {
            std::cout << "Implementation" << std::endl;
        }
};

int main() {
    // PureVirtual pure; // This will cause an error because PureVirtual is an abstract class
    Impl impl;
    impl.print();

    return 0;
}