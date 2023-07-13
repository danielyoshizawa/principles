#include <iostream>

class Data
{
public:
    Data() {
        std::cout << "Constructing Data" << std::endl;
    }
    ~Data() {
        std::cout << "Destructing Data" << std::endl;
    }
};

class Base
{
protected:
    std::string id;

public:
    Base(const std::string &id) : id{id}
    {
        std::cout << "Constructing Base Class id : " << id << std::endl;
    }

    ~Base()
    { // Not defining constructor as virtual for demonstration
        std::cout << "Destructing Base Class id : " << id << std::endl;
    }

    // This function is only to create a vtable 
    virtual void print() {
        std::cout << "Base Object" << std::endl;
    }
};

class Derived : public Base
{
private:
    Data *ptr;

public:
    Derived(const std::string &id) : Base{id}
    {
        std::cout << "Constructing Derived Class id : " << id << std::endl;
        // Allocating Data Object into the heap to demonstrate a memory leak
        // check valgrind mencheck to verify it.
        ptr = new Data;
    }
    ~Derived()
    {
        std::cout << "Destructing Derived Class id : " << id << std::endl;
        delete ptr;
        ptr = nullptr;
    }

    void print() override {
        std::cout << "Derived Object" << std::endl;
    }
};

int main()
{
    // For this exercise we will test what happens when we cast
    // a derived class to its base and call a non-virtual destructor
    Derived * d = new Derived{"Derived"};
    d->print(); // vtable points this function to the derived version
    
    // Casting Derived to Base
    Base * b = dynamic_cast<Base *>(d);
    b->print(); // vtable point this function to the derived version
    
    // When we delete the Base object without a virtual destructor
    // the Derived destructor will not be called.
    // If you have any memory allocated on the Derived class, as in our example
    // you will create a memory leak, and possible some undefined behavior.
    delete b;
    b = nullptr;
}

// Output from Valgrind
// ==4770== HEAP SUMMARY:
// ==4770==     in use at exit: 1 bytes in 1 blocks
// ==4770==   total heap usage: 4 allocs, 3 frees, 73,777 bytes allocated
// ==4770== 
// ==4770== 1 bytes in 1 blocks are definitely lost in loss record 1 of 1
// ==4770==    at 0x4840F2F: operator new(unsigned long) (vg_replace_malloc.c:422)
// ==4770==    by 0x10A65A: Derived::Derived(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&) (in Virtual)
// ==4770==    by 0x10A2FD: main (in Virtual)