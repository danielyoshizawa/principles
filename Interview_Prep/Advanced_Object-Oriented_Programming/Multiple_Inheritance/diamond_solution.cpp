#include <iostream>

// To resolve the diamond problem, you can use virtual inheritance

// Virtual inheritance ensures that only one instance of the base class is shared among 
// all derived classes, thus resolving the ambiguity.
// 
// How Virtual Inheritance Works:
// - Single Instance: Virtual inheritance ensures that only one instance of the base class exists, 
// regardless of how many times it is inherited.
// - Early Binding: The virtual base class is initialized before any non-virtual base class, 
// ensuring that the virtual base class is properly initialized before any derived classes 
// are instantiated.
//
// Memory Layout:
// - Virtual base class is placed at the end of the inheritance hierarchy.
// - Non-virtual base classes are placed before the virtual base class.
// - Derived classes are placed after the virtual base class.
//
// Virtual inheritance and v-table
// When using virtual inheritance, the compiler generates a virtual table (v-table) for each class.
// The v-table is used to resolve the correct address of the virtual base class when calling a method.
// To do that, a v-pointer is added to the object. When using the virtual inheritance the compiler
// will use the v-pointer to find the correct address of the virtual base class. Since this is a shared
// instance, the v-pointer will point to the same address in memory. Fixing the ambiguity.

class Base {
    public:
        void print() {
            std::cout << "Base" << std::endl;
        }
};

class A : public virtual Base {};
class B : public virtual Base {};

class C : public A, public B {};

int main() {
    C c;
    c.print(); // Ambiguous call to print, this will cause a compilation error! Diamond Problem

    return 0;
}