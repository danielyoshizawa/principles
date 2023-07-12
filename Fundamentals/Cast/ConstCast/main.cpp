#include <iostream>

void print(char * str) {
    std::cout << str << std::endl;
};

int main()
{
    const char * c = "Const cast in action";
    print(const_cast<char *>(c));
    return 0;
}