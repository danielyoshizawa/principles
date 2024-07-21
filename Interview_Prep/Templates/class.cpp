#include <iostream>

// Class templates allow you to create a class definition that works with different data types.

template <typename T>
class Box
{
private:
    T value;

public:
    Box(T value) : value(value) {}
    T getValue() const { return value; }
};

int main() {
    Box<int> intBox(123);
    Box<double> doubleBox(123.456);

    std::cout << "intBox value: " << intBox.getValue() << std::endl;
    std::cout << "doubleBox value: " << doubleBox.getValue() << std::endl;

    return 0;
}