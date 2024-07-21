#include <iostream>

// Template specialization allows you to define a specific implementation of a template for a 
// particular data type.

template <typename T>
class Box {
    public:
        void print() {
            std::cout << "Generic Box" << std::endl;
        }
};

// Spcecialization for int
template <>
class Box<int> {
    public:
        void print() {
            std::cout << "Specialized Box for int" << std::endl;
        }
};

int main() {
    Box<int> intBox;
    intBox.print();

    Box<double> doubleBox;
    doubleBox.print();

    return 0;
}