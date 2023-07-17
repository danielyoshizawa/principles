#include <iostream>
#include <exception>

// Basic implementation of a Smart Pointer
// A Smart Pointer is a wrapper class over a pointer
// with an operator like * or -> overloaded.
// The objects of the smart pointer class look like normal pointers.
// But, unlike Normal Pointers it can deallocate and free destroyed object memory.

template <class T>
class SmartPointer
{
    T *ptr; // Actual pointer or Raw Pointer
public:
    // Cannot be used to for implicit conversions and copy-initializations
    explicit SmartPointer(T *p = nullptr)
    {
        std::cout << "Constructor" << std::endl;
        ptr = p;
    }
    // RAII, when goes out of scope it releases its resources
    // also, in case of exception during the execution
    // the destructor will be called, releasing the memory.
    // Note : In case of exception, is only guaranted that the
    // destructor will be called if the exception is caught.
    ~SmartPointer()
    {
        std::cout << "Destructor" << std::endl;
        delete ptr;    // Avoids memory leak
        ptr = nullptr; // Avoids dangling pointer
    }
    T &operator*()
    {
        return *ptr; // Operator * overload for regular operations
    }
    // Overloading arrow operator,
    // so that members of T can be accessed like a pointer
    // (useful if T represents a class or struct or union type)
    T *operator->()
    {
        return ptr;
    }
};

class Data
{
    int a;
    std::string id;

public:
    Data(std::string id) : a{10}, id{id}
    {
        std::cout << "Data Constructor : " << id << std::endl;
    }
    ~Data()
    {
        std::cout << "Data Destructor : " << id << std::endl;
    }
    int get() const
    {
        return a;
    }
};

int main()
{
    try
    {
        SmartPointer<Data> smtPtr{new Data{"Smart"}};
        Data &ref = *smtPtr;
        Data * raw = new Data{"Raw"};
        std::cout << "Using Reference : " << ref.get() << std::endl;
        std::cout << "Data arrow function : " << smtPtr->get() << std::endl;

        throw std::runtime_error("Forcing Exception");
        // Raw pointer will not be deleted
        delete raw;
    }
    catch (const std::exception &e)
    {
        std::cout << "Treating exception : " << e.what() << std::endl;
    }

    return 0;
}