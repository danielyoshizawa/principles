// Stack
// Stacks are a type of container adaptor, specifically designed to operate in a LIFO context
// (last-in first-out), where elements are inserted and extracted only from one end of the container.

// stacks are implemented as container adaptors, which are classes that use an encapsulated object
// of a specific container class as its underlying container, providing a specific set of member
// functions to access its elements. Elements are pushed/popped from the "back" of the specific
// container, which is known as the top of the stack.

// The underlying container may be any of the standard container class templates or
// some other specifically designed container class. The container shall support the
// following operations:
// empty
// size
// back
// push_back
// pop_back

// The standard container classes vector, deque and list fulfill these requirements.
// By default, if no container class is specified for a particular stack class instantiation,
// the standard container deque is used.

#include <iostream>
#include <stack>
#include <list>
#include <vector>
#include <deque>

void print(auto s)
{
    while (s.size())
    {
        std::cout << s.top() << " ";
        s.pop();
    }
    std::cout << std::endl;
}

void manipulate(auto &s)
{
    std::cout << "Adding 4 elements using stack::push" << std::endl;
    s.push(0);
    s.push(1);
    s.push(2);
    s.push(3);
    print(s);
    std::cout << "Removing element using stack::pop" << std::endl;
    s.pop();
    print(s);
}

int main()
{
    std::cout << "Creating a stack using deque" << std::endl;
    std::stack<int, std::deque<int>> dequeStack; // Deque is the default container, second template argument can be omitted
    manipulate(dequeStack);

    std::cout << "Creating a stack using vector" << std::endl;
    std::stack<int, std::vector<int>> vectorStack;
    manipulate(vectorStack);

    std::cout << "Creating a stack using list" << std::endl;
    std::stack<int, std::list<int>> listStack;
    manipulate(listStack);

    return 0;
}