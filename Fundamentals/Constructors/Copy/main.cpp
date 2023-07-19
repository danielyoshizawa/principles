// A copy constructor is a member function that initializes an object
// using another object of the same class.

#include <iostream>

class A
{
    int i;
    double d;

public:
    A(int i, double d) : i{i}, d{d}
    {
        std::cout << "Parameterized Constructor : A(int, double)" << std::endl;
    }
    A(const A &a)
    {
        std::cout << "Copy constructor : A(const A &a)" << std::endl;
    }
    // Removing move semantics
    // A(A &&a) = delete;
    // A &operator=(A &&a) = delete;
};

class B
{
private:
    A a;

public:
    B() : a(A{1, 1.4}) {}
    // Passing an object by value will call the copy constructor to create a temporary object
    void func(A a)
    {
        std::cout << "Inside the B::func(A)" << std::endl;
    }

    // Returning an object by value will call the copy constructor
    A funcReturn()
    {
        std::cout << "Returning an object by value" << std::endl;
        return a;
    }
};

// Making objects of a class non-copiable
class C
{
    // Make the copy construct private or
private:
    // C(C const &c){};
    // C & operator=(C const &c){};
public:
    C() = default;
    // Delete the copy constructor
    C(C const &c) = delete;
    // Delete the assignment operator
    C &operator=(C const &c) = delete;
};

int main()
{
    A a1{10, 8.9};
    A a2{a1};     // Implicit call
    A a3 = A{a2}; // Explicit call
    B b;
    std::cout << "Passing an object by value" << std::endl;
    b.func(a1);
    b.funcReturn(); // Not assigning to anything to show that its called on return not on assignment

    C c1;
    // C c2{c1}; // Error : function "C::C(const C &b)" cannot be referenced -- it is a deleted function
    // Calling the assignment operator to make a copy won't work as well.
    // C c2;
    // c1 = c2;
    return 0;
}

// NOTES :
// It is, however, not guaranteed that a copy constructor will be called in all these cases,
// because the C++ standard allows the compiler to optimize the copy away in certain cases,
// one example is the return value optimization (sometimes referred to as RVO)
// RVO is a technique that gives the compiler some additional power to terminate the temporary
// object created which results in changing the observable behavior/characteristics of the final
// program.