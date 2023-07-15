#include <iostream>

int main()
{
    // Allocating a pointer on the stack but not pointing to a valid address,
    // will create a wild pointer, we can check trying to access its value.
    int * i;
    std::cout << "Address of wild pointer : " << &i << std::endl;
    std::cout << "Trying to access its value" << std::endl;
    std::cout << *i << std::endl; // Segmentation Fault
    return 0;
}