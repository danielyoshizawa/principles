#include <iostream>

class Singleton
{
private:
    int data;
    static Singleton * ptr;
    Singleton() : data(0) {
        std::cout << "Private contructor" << std::endl;
    }
public:
    Singleton(const Singleton &) = delete;

    void Set(int d) {
        data = d;
    }

    void Print() {
        std::cout << "Holding data : " <<  data << std::endl;
    }

    static Singleton * Instance() {
        if (ptr == nullptr) {
            ptr = new Singleton();
        }

        return ptr;
    }
};

Singleton * Singleton::ptr = nullptr;

int main() {
    Singleton * sing = Singleton::Instance();
    std::cout << "Setting data to 10 through the first pointer" << std::endl;
    sing->Set(10);
    std::cout << "Printing data through the first pointer" << std::endl;
    sing->Print();
    std::cout << "Calling Singleton::Instance on a new pointer" << std::endl;
    Singleton * sing2 = Singleton::Instance();
    std::cout << "Setting data to 20 through the second pointer" << std::endl;
    sing2->Set(20);
    std::cout << "Printing data through the first pointer" << std::endl;
    sing->Print();
    std::cout << "Printing data through the second pointer" << std::endl;
    sing2->Print();

    std::cout << "Address to where the first pointer points : " << sing << std::endl;
    std::cout << "Address to where the second pointer points : " << sing2 << std::endl;

    return 0;
}