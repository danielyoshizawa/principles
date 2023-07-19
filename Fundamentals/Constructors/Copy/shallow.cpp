// Shallow and Deep copy
// Shallow copy does memory dumping bit-by-bit from one object to another.
// Deep copy is copy field by field from object to another.
// Deep copy is achieved using copy constructor and or overloading assignment operator.

#include <iostream>

// Shallow copy Problem
struct Data
{
    int i;
    double d;
};

class A
{
private:
    int i;
    Data *data; // Heap allocated memory, needs deep copy!

public:
    A() : i{10}, data{new Data{1, 1.2}} {}
    void setData(int i, double d)
    {
        data->i = i;
        data->d = d;
    }
    void print(std::string const& id) {
        std::cout << "Data " << id << " : int = " << data->i << std::endl;
        std::cout << "Data " << id << " : double = " << data->d << std::endl;
    }
};

int main()
{
    A a1;
    A a2{a1}; // Shallow copy
    a1.print("A1"); // Data before change
    a2.print("A2");
    a1.setData(99, 12.34);
    a1.print("A1"); // Data after change
    a2.print("A2");
    return 0;
}

// NOTE : On a shallow copy, the address of any pointer data member
// will be copied, making 2 objects point to the same address.