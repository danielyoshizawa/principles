// List (Double Linked List)
// Lists are sequence containers that allow constant time insert and erase operations 
// anywhere within the sequence, and iteration in both directions.
// List containers are implemented as doubly-linked lists;
// They are very similar to forward_list: The main difference being that forward_list objects 
// are single-linked lists, and thus they can only be iterated forwards, 
// in exchange for being somewhat smaller and more efficient.
// Compared to other base standard sequence containers (array, vector and deque), 
// lists perform generally better in inserting, 
// extracting and moving elements in any position within the container for which an iterator 
// has already been obtained, and therefore also in algorithms that make intensive use of these, 
// like sorting algorithms.
// The main drawback of lists and forward_lists compared to these other sequence containers 
// is that they lack direct access to the elements by their position;
// Container properties:
// Sequence           : Elements in sequence containers are ordered in a strict linear sequence.
//                      Individual elements are accessed by their position in this sequence.
// Doubly-linked list : Each element keeps information on how to locate the next and the 
//                      previous elements, allowing constant time insert and erase operations before or after a specific element (even of entire ranges), but no direct random access.
// Allocator-aware    : The container uses an allocator object to dynamically handle its 
//                      storage needs. 

#include <iostream>
#include <list>
#include <functional>

void printElements(auto lt) {
    for (auto n : lt) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
};

int main()
{
    std::cout << "Creating our List (Double Linked List)" << std::endl;
    std::list<int> lt;
    std::cout << "Adding 2 elements to the front of the list list::push_front" << std::endl;
    lt.push_front(4);
    lt.push_front(7);
    printElements(lt);
    std::cout << "Adding 2 elements to the back of the list list::push_back" << std::endl;
    lt.push_back(6);
    lt.push_back(1);
    printElements(lt);
    std::cout << "Sorting the list with std::less list::sort" << std::endl;
    lt.sort(std::less());
    printElements(lt);
    std::cout << "Splicing elements to a new list list::splice" << std::endl;
    std::list<int> splice;
    std::list<int>::iterator it {std::begin(lt)};
    std::advance(it, 2);
    splice.splice(splice.begin(), lt, it, std::end(lt));
    printElements(lt);
    printElements(splice);
    std::cout << "Swapping the content of both list list::swap" << std::endl;
    lt.swap(splice);
    printElements(lt);
    printElements(splice);

    return 0;
}