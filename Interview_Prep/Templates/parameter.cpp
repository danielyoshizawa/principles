#include <iostream>

// Tempaltes can take different types of parameters:
// - Type parameters : typename T or class T
// - Non-Type Parameters: template<int N>

template <typename T, int size>
class Array
{
private:
    T arr[size];

public:
    int getSize() const { return size; }
};

int main()
{
    Array<int, 10> intArray;
    std::cout << "Array size: " << intArray.getSize() << std::endl;
    return 0;
}