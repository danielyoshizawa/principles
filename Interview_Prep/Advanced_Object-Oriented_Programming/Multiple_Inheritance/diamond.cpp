#include <iostream>

class Base {
    public:
        void print() {
            std::cout << "Base" << std::endl;
        }
};

class A : public Base {};
class B : public Base {};

class C : public A, public B {};

int main() {
    C c;
    // Explanation:
    // 1. C inherits from A and B
    // 2. A and B both inherit from Base
    // 3. C has two Base objects, which causes ambiguity
    // c.print(); // Ambiguous call to print, this will cause a compilation error! Diamond Problem
    // Output:
    // error: request for member ‘print’ is ambiguous

    return 0;
}