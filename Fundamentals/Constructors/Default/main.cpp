// What is a constructor?
// - Constructor is a member function of a class, whose name is same as the class name
// - Constructor is a special type of member function that is used to initialize the data members
// for an object of a class automatically, when an object of the same class is created
// - Constructor is invoked at the time of object creation. It constructs the values
// i.e. provides data for the object that is why it is known as constructor.
// - Constructor do not return value, hence they do not have a return type.
// - Constructors can be overloaded
// - Constructor can not be declared virtual
// - Constructor cannot be inherited
// - Addresses of Constructor cannot be referred
// - Constructor make implicit calls to new and delete operators during memory allocation

#include <iostream>

// Default Contructor is the constructor which doesn't take any arguments.
// It has no parameters. It is also called a zero-argument constructor.
class A
{
public:
    // Constructor within the class
    A()
    {
        std::cout << "Constructor within the class - Class A" << std::endl;
    }
};

class B
{
public:
    B();
};

B::B()
{
    std::cout << "Constructor outside the class - Class B" << std::endl;
};

class C
{
public:
    void print()
    {
        std::cout << "The compiler generated a default contructor for me - Class C" << std::endl;
    }
};

int main()
{
    // Calling default constructors
    A a;
    B b;
    C c;
    c.print();
    // Assignment will call the default contructor
    A a2;
    a2 = a;

    return 0;
}