// - Overloaded constructors essentially have the same name (exact name of the class)
// and different by number and type of arguments.
// - A constructor is called depending upon the number and type of arguments passed.
// - While creating the object, arguments must be passed to let compiler know,
// which constructor needs to be called.

#include <iostream>

class A
{
private:
    int i;
    double d;

public:
    A(int i) : i{i}
    {
        std::cout << "Calling overloaded constructor A(int i)" << std::endl;
    }
    A(double d) : d{d}
    {
        std::cout << "Calling overloaded constructor A(double d)" << std::endl;
    }
    A(int i, double d) : i{i}, d{d}
    {
        std::cout << "Calling overloaded constructor A(int i, double d)" << std::endl;
    }
};

int main()
{
    int i = 10;
    double d = 5.4;
    A a1{i};
    A a2{d};
    A a3{i,d};
    A a4{4, 8.9};
}