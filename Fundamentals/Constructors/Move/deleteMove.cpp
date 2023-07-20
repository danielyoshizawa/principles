// Same example as the main one, only this time
// we deleted the move assignment and move constructor
// to force the compiler to make copies, so we can compare
// the workflow of both versions

#include <iostream>

struct Data
{
    int i;
    double d;
};

class A
{
private:
    Data *data;
    std::string id;

public:
    A() : data{nullptr}, id{"default"}
    {
        std::cout << "ID :: " << id << " | Default Constructor" << std::endl;
    }
    A(int i, double d, std::string id) : data{new Data{i, d}}, id{id}
    {
        std::cout << "ID :: " << id <<  " | Parameterized Constructor" << std::endl;
    }
    // Deep Copy constructor - lvalue
    A(A const &lref)
    {
        data = new Data{lref.data->i, lref.data->d};
        std::cout << "ID :: " << id <<  " | Copy Constructor" << std::endl;
    }
    // Deep Copy Assignment operator - lvalue
    A &operator=(A const &lref)
    {
        std::cout << "ID :: " << id <<  " | Copy assignment operator" << std::endl;
        data = new Data{lref.data->i, lref.data->d};
        return *this;
    }
    // Move constructor - rvalue (Deleted)
    A(A &&rref) = delete;
    // Move assignment operator - rvalue (Deleted)
    A &operator=(A &&rref) = delete;
    ~A()
    {
        delete data;
        data = nullptr;
        std::cout << "ID :: " << id <<  " | Destructor" << std::endl;
    }
    void print()
    {
        std::cout <<  "ID :: " << id << " | ";
        if (data == nullptr)
        {
            std::cout << "I don't own data resource" << std::endl;
            return;
        }
        std::cout << "Data int : " << data->i << " - Data double : " << data->d << std::endl;
    }
};

class B
{
private:
    A *a;

public:
    B() : a{new A}
    {
    }
    ~B()
    {
        delete a;
        a = nullptr;
    }
    void receiveParamByValue(A a)
    {
        a.print();
    }
    void receiveParamBy(A &a)
    {
        std::cout << "Receive Para by LRef" << std::endl;
        a.print();
    }
    void receiveParamBy(A &&a)
    {
        std::cout << "Receive Param By RRef" << std::endl;
        a.print();
    }
};
int main()
{
    A a1{1, 1.8, "A1"};
    A a2;
    std::cout << "Printing a1" << std::endl;
    a1.print();
    std::cout << "Moving a1 to a2" << std::endl;
    a2 = a1; // NOTE : Changed from previous example
    std::cout << "Printing a1" << std::endl;
    a1.print();
    std::cout << "Printing a2" << std::endl;
    a2.print();
    std::cout << "-----------------------------" << std::endl;

    A a3; // Calls the default construtor
    A tmp = A{4, 5.6, "A3"}; // NOTE : Changed from previous example
    std::cout << "Using move assign operator" << std::endl;
    a3 = tmp; // Using the move assignment operator instead of copy
    std::cout << "-----------------------------" << std::endl;

    B b;
    A a{2, 2.6, "A4"};
    std::cout << "Calling functions of class B" << std::endl;
    std::cout << "ReceiveParamByValue(A a)" << std::endl;
    b.receiveParamByValue(a); // Calls copy constructor (lvalue)
    std::cout << "ReceiveParamBy(A & a)" << std::endl;
    b.receiveParamBy(a); // Do nothing, its a reference
    std::cout << "ReceiveParamBy(A && a)" << std::endl;
    b.receiveParamBy(A{3, 4.5, "A5"}); // Calls parameterized constructor
    std::cout << "-----------------------------" << std::endl;

    return 0;
}