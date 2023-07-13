#include <iostream>

class Base
{
protected:
    std::string id;

public:
    Base(std::string id) : id{id}
    {
        std::cout << "Constructing Base Class id : " << id << std::endl;
    }
    ~Base()
    {
        std::cout << "Destructing Base Class id : " << id << std::endl;
    }
};

class Derived : public Base
{
public:
    Derived(std::string id) : Base(id)
    {
        std::cout << "Constructing Derived Class id : " << id << std::endl;
    }
    ~Derived()
    {
        std::cout << "Destructing Derived Class id : " << id << std::endl;
    }
};

int main()
{
    // The order of construction and destruction of hierarchies
    // 1. Memory for derived is set aside (enough for both the Base and Derived portion)
    // 2. The appropriate Derived constructor is called
    // 3. The Base object is constructed first using the appropriate base constructor.
    //    If no base constructor is specified, the default constructor will be used.
    // 4. The member initializer list initialize the variables
    // 5. The body of the constructor executes
    // 6. Control is returned to the caller.
    Derived *d = new Derived{"Derived"};
    // When a derived class is destroyed, each destructor is called in 
    // reverse order of construction.
    delete d;
}