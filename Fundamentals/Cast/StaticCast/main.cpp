#include <iostream>

class Base
{
};
class Derived : public Base
{
};

int main()
{
    // Static cast can be used to any implicit conversion
    double d = 3.14156;
    int x = d;
    int y = static_cast<int>(d);
    double d2 = static_cast<double>(y);
    std::cout << "Double to int implicit conversion : " << x << std::endl;
    std::cout << "Double to int using static_cast : " << y << std::endl;
    std::cout << "Double to Int to Double : " << d2 << std::endl;

    // Static cast can be used to cast from Derived to Base
    Derived derived;
    Base *base = static_cast<Base *>(&derived);
    // But also from Base to Derived, which can lead to incomplete objects
    Derived *otherDerived = static_cast<Derived *>(base);

    return 0;
}