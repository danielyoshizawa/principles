// Forward List
// Forward lists are sequence containers that allow constant time insert 
// and erase operations anywhere within the sequence.
// Forward lists are implemented as singly-linked lists.
// Compared to other base standard sequence containers (array, vector and deque), 
// forward_list perform generally better in inserting, extracting and moving elements 
// in any position within the container, and therefore also in algorithms that 
// make intensive use of these, like sorting algorithms.
// The main drawback of forward_lists and lists compared to these other sequence containers 
// is that they lack direct access to the elements by their position.
// To obtain the size of a forward_list object, you can use the distance algorithm 
// with its begin and end, which is an operation that takes linear time.

// Container properties
// Sequence        : Elements in sequence containers are ordered in a strict linear sequence. 
//                   Individual elements are accessed by their position in this sequence.
// Linked list     : Each element keeps information on how to locate the next element, 
//                   allowing constant time insert and erase operations after a specific element 
//                   (even of entire ranges), but no direct random access.
// Allocator-aware : The container uses an allocator object to dynamically handle its storage needs.

#include <iostream>
#include <forward_list>
#include <functional>

bool higherThanTwelve(const int& value)
{
    return value > 12;
};

void printElements(auto fList) {
    for (auto n : fList) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
};

int main()
{
    std::cout << "Creating our Forward List (Single linked list)" << std::endl;
    std::forward_list<int> fList;
    std::cout << "Adding 2 elements at the beginning of the list forward_list::push_front" << std::endl;
    fList.push_front(0);
    fList.push_front(1);
    printElements(fList);
    std::cout << "Inserting an element between the other elements forward_list::insert_after" << std::endl;
    std::forward_list<int>::iterator it = std::begin(fList);
    fList.insert_after(it, 8);
    printElements(fList);
    std::cout << "Inserting an element after the last element inserted forward_list::insert_after" << std::endl;
    ++it;
    fList.insert_after(it, 9);
    printElements(fList);
    std::cout  << "Adding a couple more elements forward_list::push_front" << std::endl;
    fList.push_front(11);
    fList.push_front(12);
    fList.push_front(13);
    fList.push_front(14);
    fList.push_front(15);
    printElements(fList);
    std::cout << "Sorting the list with std::greater forward_list::sort" << std::endl;
    fList.sort(std::greater<int>());
    printElements(fList);
    std::cout << "Removing all elements higher than 12 forward_list::remove_if" << std::endl;
    fList.remove_if(higherThanTwelve);
    printElements(fList);
    std::cout << "Slicing the list into two subsets forward_list::slice_after" << std::endl;
    std::forward_list<int> slice;
    it = std::begin(fList);
    std::advance(it, 2);
    slice.splice_after(slice.before_begin(), fList, it, std::end(fList));
    printElements(fList);
    printElements(slice);

    return 0;
}