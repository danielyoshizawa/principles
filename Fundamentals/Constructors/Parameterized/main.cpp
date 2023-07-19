// Parameterized Constructor : It is possible to pass arguments to constructors.
// NOTE : When the parameterized constructor is define and no default constructor
// is defined explicitly, the compiler will not implicity call the default constructor
// and hence creating a simple object.

#include <iostream>

class A
{
private:
    int i;

public:
    A(int i) : i{i} // initialization list
    {
        std::cout << "Parameterized constructor, receiving an integer i : " << i << std::endl;
    }
};

int main()
{
    // A a; // Don't have a default constructor
    A a{1};      // Implicity Call
    A a2 = A{2}; // Explicit Call
    return 0;
}