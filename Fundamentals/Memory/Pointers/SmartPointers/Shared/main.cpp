#include <iostream>
#include <string>
#include <memory>

class Data
{
    std::string id;

public:
    Data(std::string id) : id{id}
    {
        std::cout << "Data Constructor : " << id << std::endl;
    }
    ~Data()
    {
        std::cout << "Data Destructor : " << id << std::endl;
    }
    // Copy constructor
    // Called when passing by value
    Data(const Data & d) {
        id = d.id;
        std::cout << "Copy constructor : " << id << std::endl;
    }
    void print() const
    {
        std::cout << "Data Id : " << id << std::endl;
    }
};

void function(const Data & dt) {
    std::cout << "Const Ref Function : ";
    dt.print();
}

void function(const Data * dt) {
    std::cout << "Const Pointer Function : ";
    dt->print();
}

void function_value(Data dt) {
    std::cout << "Value function : ";
    dt.print();
}

int main()
{
    std::shared_ptr<Data> s_ptr{new Data{"D01"}};
    s_ptr->print();

    std::cout << "Counter : " << s_ptr.use_count() << std::endl;

    std::shared_ptr<Data> s_ptr2;
    s_ptr2 = s_ptr; // Sharing ownership

    std::cout << "Counter : " << s_ptr.use_count() << std::endl;

    s_ptr2->print();

    // SmartPointer initialization using new vs make_shared
    // From https://stackoverflow.com/a/9302360
    // make_shared is (in practice) more efficient, 
    // because it allocates the reference control block together 
    // with the actual object in one single dynamic allocation.
    // By contrast, the constructor for shared_ptr that takes a 
    // naked object pointer must allocate another dynamic variable 
    // for the reference count.
    // The trade-off is that make_shared (or its cousin allocate_shared) 
    // does not allow you to specify a custom deleter, 
    // since the allocation is performed by the allocator.
    //(This does not affect the construction of the object itself. 
    // From Object's perspective there is no difference between the two versions.
    // What's more efficient is the shared pointer itself, not the managed object.)
    std::shared_ptr<Data> s_ptr3 = std::make_shared<Data>("D02");
    s_ptr3->print();
    function(*s_ptr3);
    function(s_ptr3.get());
    function_value(*s_ptr3); // Calls copy constructor and deletes the temporary object when out of scope
    std::cout << "After passing by value : count : " << s_ptr3.use_count() << std::endl;

    return 0;
}