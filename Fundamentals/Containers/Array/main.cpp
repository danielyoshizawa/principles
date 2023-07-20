#include <iostream>
#include <array>

void printElements(auto arr) { // parameter auto - C++ 20
    std::cout << "Array elements : " << std::endl;
    for (auto n : arr)
    {
        std::cout << n << " ";
    }
    std::cout << std::endl;
}

int main()
{
    std::array<int, 10> myArray { 0,1,2,3,4,5,6,7,8,9 };
    std::array<int, 10> fillArray;
    printElements(myArray);

    std::cout << "First element Array::front" << std::endl;
    std::cout << myArray.front() << std::endl;
    std::cout << "Last element Array::back" << std::endl;
    std::cout << myArray.back() << std::endl;
    std::cout << "Third element Array::at" << std::endl;
    std::cout << myArray.at(2) << std::endl;
    std::cout << "Filling a second array Array::fill" << std::endl;
    fillArray.fill(8);
    printElements(fillArray);
    std::cout << "Swap arrays Array::swap" << std::endl;
    myArray.swap(fillArray);
    std::cout << "First Array" << std::endl;
    printElements(myArray);
    std::cout << "Second Array" << std::endl;
    printElements(fillArray);
    
    return 0;
}