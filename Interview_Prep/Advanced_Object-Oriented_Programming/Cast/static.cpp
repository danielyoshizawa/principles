#include <iostream>

// Static cast
// static_cas is used for compile-time type conversions. It is the most common cast and can be used for:
// 1. Converting between related types (e.g., upcasting and downcasting in inheritance hierarchies)
// 2. Converting numeric types (e.g., int to float)
// 3. Converting pointers and references to related types.
// 4. Converting between pointer-to-member types (e.g., from pointer-to-class to pointer-to-struct)
// 5. Converting between function pointer types (e.g., from void (*)(int) to void (*)(double))

// Use static_cast for most type conversions: it is the most versitile and can be used for upcasting and downcasting.

// static_cast | Compile-time type conversions | No runtime checks | Related Types, numeric conversions

class Base {
    public:
    virtual void print() { std::cout << "Base::print" << std::endl; }
};

class Derived : public Base {
    public:
    void print() override { std::cout << "Derived::print" << std::endl; }
};

int main() {
    Base * basePtr = new Derived();
    Derived * derivedPtr = static_cast<Derived*>(basePtr); // Downcasting
    derivedPtr->print();

    // Since a v-table was created the call to print will always point to the Derived class
    basePtr = static_cast<Base*>(derivedPtr); // Upcasting
    basePtr->print();

    delete basePtr;

    return 0;
}