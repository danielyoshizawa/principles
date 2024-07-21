#include <iostream>

class A {
    public:
        void print() {
            std::cout << "A" << std::endl;
        }

        void print_A() {
            std::cout << "A" << std::endl;
        }
};

class B {
    public:
        void print() {
            std::cout << "B" << std::endl;
        }

        void print_B() {
            std::cout << "B" << std::endl;
        }
};

class C : public A, public B {
    public:
        void print() {
            std::cout << "C" << std::endl;
        }

        void print_C() {
            std::cout << "C" << std::endl;
        }

        void call_base_prints() {
            A::print(); // Explicitly call A's print
            B::print(); // Explicitly call B's print
        }
};

int main() {
    C c;
    c.print();
    c.print_A();
    c.print_B();
    c.print_C();
    c.call_base_prints(); // Demonstrate calling base class methods explicitly
    return 0;
}