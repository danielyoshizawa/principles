#include <iostream>
#include <memory>

class Data
{
    std::string id;

public:
    Data(std::string id) : id{id}
    {
        std::cout << "Constructor : " << id << std::endl;
    }
    ~Data()
    {
        std::cout << "Destructor : " << id << std::endl;
    }
    void print() const
    {
        std::cout << "Data id : " << id << std::endl;
    }
};

void func(const Data &const_ref)
{
    const_ref.print();
};

void func(Data * pointer) {
    pointer->print();
};

void func_value(Data value) { // Creates a copy
    value.print();
} // Temporary copy is destructed

int main()
{
    std::unique_ptr<Data> d_ptr{new Data{"U01"}};

    // Passing data to functions
    func(*d_ptr);
    func(d_ptr.get());
    func_value(*d_ptr);

    Data &ref = *d_ptr;
    // Gets the pointer, but resource release still unique ptr responsibility.
    Data *raw = d_ptr.get();
    d_ptr->print();
    ref.print();
    raw->print();

    std::unique_ptr<Data> d_ptr2;
    // d_ptr2 = d_ptr; // Cant share ownership
    d_ptr2 = std::move(d_ptr); // Only change ownership
    d_ptr2->print();
    // d_ptr->print(); // Segmentation fault

    raw = d_ptr2.release(); // Unique pointer is no longer responsible for resource release.

    delete raw;
    raw = nullptr;

    return 0;
}