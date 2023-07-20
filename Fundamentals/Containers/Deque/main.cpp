// Deque - Double Ended Queue
// Similar to vectors, but wit efficient insertion and deletion of elements also at
// the begining of the sequence, and not only its end. Deques are not guaranteed to store
// all elements in contiguous storage location, accessing elements in a deque by offsetting
// a pointer to another element causes undefined behavior.
// For operations that involve frequent insertion or removals of elements at positions other
// than the beginning or the end, deques perform worse and have less consistent iterators and
// references than lists and forward lists.

// Container properties
// Sequence        : Elements in sequence containers are ordered in a strict linear sequence.
//                   individual elements are accessed by theis position in this sequence.
// Dynamic Array   : Generally implemented as a dynamic array, it allows direct access to any
//                   element in the sequence and provides relatively fast addition/removal
//                   of elements at the beginning or the end of the sequence.
// Allocator-aware : The container uses an allocator object to dynamically handle its storage needs.

#include <iostream>
#include <deque>

void printElements(auto dq) {
    for (auto n: dq) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
}

int main()
{
    std::cout << "Creating our Deque" << std::endl;
    std::deque<int> first {0, 1, 2, 3, 4};
    printElements(first);
    std::cout << "Pushing element to the front Deque::push_front" << std::endl;
    first.push_front(5);
    printElements(first);
    std::cout << "Pushing element to the back Deque::push_back" << std::endl;
    first.push_back(8);
    printElements(first);
    std::cout << "Getting the third element Deque::at" << std::endl;
    std::cout << first.at(2) << std::endl;
    std::cout << "Removing the first two elements Deque::pop_front" << std::endl;
    first.pop_front();
    first.pop_front();
    printElements(first);

    return 0;
}