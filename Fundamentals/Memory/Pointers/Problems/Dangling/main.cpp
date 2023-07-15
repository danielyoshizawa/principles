#include <iostream>

int main()
{
    // To create a dangling pointer, deletes the memory where it points to
    // and keep the pointer pointing to the same address.
    // It will cause undefined behavior.
    int * i = new int(5);
    std::cout << "Memory Address of i before deletion : " << &i << std::endl;
    std::cout << "Value of i before deletion : " << *i << std::endl;
    delete i;
    std::cout << "Memory Address of i after deletion : " << &i << std::endl;
    std::cout << "Value of i after deletion : " << *i << std::endl;
    return 0;
}