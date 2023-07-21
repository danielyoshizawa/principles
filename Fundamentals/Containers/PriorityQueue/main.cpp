// Priority Queue
// Priority queues are a type of container adaptors, specifically designed such 
// that its first element is always the greatest of the elements it contains, 
// according to some strict weak ordering criterion.

// This context is similar to a heap, where elements can be inserted at any moment, 
// and only the max heap element can be retrieved (the one at the top in the priority queue).

// Priority queues are implemented as container adaptors, which are classes that use 
// an encapsulated object of a specific container class as its underlying container, 
// providing a specific set of member functions to access its elements. 
// Elements are popped from the "back" of the specific container, which is 
// known as the top of the priority queue.

// The underlying container may be any of the standard container class templates or 
// some other specifically designed container class. The container shall be accessible 
// through random access iterators and support the following operations:
// empty()
// size()
// front()
// push_back()
// pop_back()

// The standard container classes vector and deque fulfill these requirements. 
// By default, if no container class is specified for a particular priority_queue 
// class instantiation, the standard container vector is used.

// Support of random access iterators is required to keep a heap structure internally at all times. 
// This is done automatically by the container adaptor by automatically calling the 
// algorithm functions make_heap, push_heap and pop_heap when needed.

#include <iostream>
#include <queue>
#include <vector>
#include <deque>
#include <functional>

void print(auto & q)
{
    while (q.size())
    {
        std::cout << q.top() << " ";
        q.pop();
    }
    std::cout << std::endl;
}

int main()
{ 
    std::cout << "Creating our priority queue using std::vector" << std::endl;
    std::priority_queue<int, std::vector<int>> pq; // Default Comparison is std::less
    std::cout << "Adding elements to our priority queue using priority_queue::push" << std::endl;
    pq.push(12);
    pq.push(56);
    pq.push(9);
    std::cout << "Popping the elements priority_query::pop and printing using priority_query::top" << std::endl;
    print(pq);

    std::cout << "Creating our priority queue using std::deque and std::greater" << std::endl;
    std::priority_queue<int, std::deque<int>, std::greater<int>> pq2;
    std::cout << "Adding elements to our priority queue using priority_queue::push" << std::endl;
    pq2.push(12);
    pq2.push(56);
    pq2.push(9);
    std::cout << "Popping the elements priority_query::pop and printing using priority_query::top" << std::endl;
    print(pq2);
    return 0;
}