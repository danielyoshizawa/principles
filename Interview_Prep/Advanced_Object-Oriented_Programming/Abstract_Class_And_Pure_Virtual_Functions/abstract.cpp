#include <iostream>

// This class is an abstract class because it has a pure virtual function.
// It can't be instantiated directly. You need to inherit from it and implement
// the pure virtual function.
class Abstract {
    public:
        virtual void print() = 0; // Pure virtual function
};

class Impl : public Abstract {
    public:
        void print() override {
            std::cout << "Impl" << std::endl;
        }
};

int main() {
    // Abstract abs; // This will cause a compilation error
    Impl impl;
    impl.print();
    // Holding the implementation pointer in the Abstract class
    Abstract* abs = &impl;
    abs->print();

    return 0;
}