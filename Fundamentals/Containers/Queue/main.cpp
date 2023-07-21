// Queue - FIFO Queue
// queues are a type of container adaptor, specifically designed to operate in a FIFO context
// (first-in first-out), where elements are inserted into one end of the container and
// extracted from the other.

// queues are implemented as containers adaptors, which are classes that use an encapsulated
// object of a specific container class as its underlying container, providing a specific
// set of member functions to access its elements.
// Elements are pushed into the "back" of the specific container and popped from its "front".

// The underlying container may be one of the standard container class template or
//  some other specifically designed container class. This underlying container shall
//  support at least the following operations:
//  empty
//  size
//  front
//  back
//  push_back
//  pop_front

// The standard container classes deque and list fulfill these requirements.
// By default, if no container class is specified for a particular queue class instantiation,
// the standard container deque is used.

#include <iostream>
#include <queue>
#include <deque>
#include <list>

void printFront(auto & q)
{
    while (q.size())
    {
        std::cout << q.front() << " ";
        q.pop();
    }
    std::cout << std::endl;
}

int main()
{
    std::cout << "Creating a Queue using deque as container" << std::endl;
    std::queue<int, std::deque<int>> qu; // Deque is the default container, this is only for show how can be done
    std::cout << "Adding elements to the queue queue::push" << std::endl;
    qu.push(0);
    qu.push(1);
    qu.push(2);
    qu.push(3);
    std::cout << "Removing elements using queue::pop" << std::endl;
    printFront(qu);
    // Same example with list instead of deque
    std::cout << "Creating a Queue using list as container" << std::endl;
    std::queue<int, std::list<int>> qu2;
    std::cout << "Adding elements to the queue queue::push" << std::endl;
    qu2.push(0);
    qu2.push(1);
    qu2.push(2);
    qu2.push(3);
    std::cout << "Removing elements using queue::pop" << std::endl;
    printFront(qu2);

    return 0;
}