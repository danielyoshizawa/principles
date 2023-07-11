#include <iostream>
#include <string>
#include <typeinfo>

template <class T>
void printSize(const std::string & typeName) {
    int size = sizeof(T);
    std::cout << typeName << " : " << size << " byte" << (size > 1 ? "s" : "") << std::endl; 
}

int main() {
    std::cout << "Data Type - sizeof" << std::endl;
    
    printSize<char>("Char");
    printSize<char16_t>("Char16_t");
    printSize<char32_t>("Char32_t");
    printSize<bool>("Bool");
    printSize<short>("Short");
    printSize<int>("Int");
    printSize<uint>("Unsigned Int");
    printSize<const int>("Const Int");
    printSize<long>("Long Int");
    printSize<long long>("Long Long Int");
    printSize<float>("Float");
    printSize<double>("Double");
    printSize<void *>("Void Pointer");
    
    return 0;
}