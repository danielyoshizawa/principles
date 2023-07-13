#include <iostream>

class Data
{
public:
    Data()
    {
        std::cout << "Constructing Data" << std::endl;
    }
    ~Data()
    {
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

    virtual ~Base() // This is the fix!
    {
        std::cout << "Destructing Base Class id : " << id << std::endl;
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
        ptr = new Data;
    }
    ~Derived()
    {
        std::cout << "Destructing Derived Class id : " << id << std::endl;
        delete ptr;
        ptr = nullptr;
    }
};

int main()
{
    // On this exercise we set the Base destructor as virtual
    // This way, when we delete the Base pointer (pointing to a Derived Object)
    // the destructor of the derived class will be called.
    // It is implementation specific, but usually this is managed in the vtable
    // since the destructor is virtual, its address is kept there,
    // this way when and object is destructed the program checks the vptr
    // and invoke the right destructor.
    Derived *d = new Derived{"Derived"};

    // Casting Derived to Base
    Base *b = dynamic_cast<Base *>(d);

    delete b;
    b = nullptr;
}

// Output from Valgrind
// ==4956== HEAP SUMMARY:
// ==4956==     in use at exit: 0 bytes in 0 blocks
// ==4956==   total heap usage: 4 allocs, 4 frees, 73,777 bytes allocated
// ==4956==
// ==4956== All heap blocks were freed -- no leaks are possible
