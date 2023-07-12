#include <iostream>

class A
{
    int internal{10};

public:
    void print() const
    {
        std::cout << "Internal data member value : " << internal << std::endl;
    }
};

int main()
{
    A a;
    int *accessingPrivate = reinterpret_cast<int *>(&a);
    std::cout << "Accessing private data member from outside of the class : " << (*accessingPrivate) << std::endl;

    a.print();
    std::cout << "Changing the internal data member through pointers" << std::endl;
    *accessingPrivate = 20;

    a.print();

    return 0;
}