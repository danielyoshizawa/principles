#include <iostream>

class A
{
    public:
    A() {
        std::cout << "Constructor A" << std::endl;
    }
    void print() {
        std::cout << "Calling print from Class A" << std::endl;
    }
};
class B : public A
{
    public:
    B() {
        std::cout << "Constructor B" << std::endl;
    }
};
class C : public A
{
    public:
    C() {
        std::cout << "Constructor C" << std::endl;
    }
};
class D : public B, public C
{
    public:
    D() {
        std::cout << "Constructor D" << std::endl;
    }
};

int main()
{
    // With out current hierarchy, we endup with two copies of the A class,
    // one from B and one from C.
    D d;
    // While this is often desired, other times you may want only one copy of
    // Class A to be shared by both B and C.
    // The problem is, if I try to call a function or access a data member 
    // from Class A, the compiler won't know which copy of class A to use.
    // d.print() // this will generate a compiler error!
    // error: request for member ‘print’ is ambiguous
}