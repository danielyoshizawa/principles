#include <iostream>
#include <exception>

class Base {

};

class Derived : public Base {

};

class BaseVirtual {
public:
    virtual void foo() {};
};

class DerivedVirtual : public BaseVirtual {

};

int main() {
    Base b;
    Base * pb;
    Derived d;
    Derived * pd;

    pb = dynamic_cast<Base*>(&d); // Ok, cast from derived to base
    
    // Not Ok, cast from non-polymorphic base to derived
    // pd = dynamic_cast<Derived*>(&b);

    BaseVirtual bv;
    BaseVirtual *pbv;
    DerivedVirtual dv;
    DerivedVirtual *pdv;

    pbv = dynamic_cast<BaseVirtual *>(&dv); // OK, cast from derived to base
    pdv = dynamic_cast<DerivedVirtual *>(&bv); // Work, cast from polymorphic base to derived

    // On the last example, the cast will return a nullptr
    if (pdv == nullptr) {
        std::cout << "Cast from polymorphic base class to derived returns a nullptr" << std::endl;
    }

    // Why does this cast is allowed if returns a nullptr?
    // It will work if the base pointer points to a derived class, 
    // meaning that the vtable of BaseVirtual* points to a valid DerivedVirtual vtable
    BaseVirtual *pbv_d = new DerivedVirtual;

    pdv = dynamic_cast<DerivedVirtual *>(pbv_d);

    if (pdv != nullptr) {
        std::cout << "Cast from base to derived works when the pointer points to a valid derived object" << std::endl;
    }

    // We worked with pointers so far, but dynamic_cast works with references too
    // what is the difference?

    BaseVirtual * pba = new BaseVirtual;
    try {
        DerivedVirtual &rda = dynamic_cast<DerivedVirtual &>(*pba);
    } catch (std::exception & ex) {
        std::cout << "Cast to reference throws an exception when it cannot perform" << std::endl;
    }

    // Casting to a reference will throw an exception if the type is not valid
    // the rules are the same for pointer, the only difference is how it is handled

    // Now a valid reference cast
    BaseVirtual *pbb = new DerivedVirtual;
    try {
        DerivedVirtual &rdb = dynamic_cast<DerivedVirtual &>(*pbb);
    } catch (std::exception & ex) {
        std::cout << "This cast will not throw" << std::endl;
    }

    std::cout << "Previous cast was valid" << std::endl;

    return 0;
}