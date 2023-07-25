// Vector
// Vectors are sequence containers representing arrays that can change in size.

// Just like arrays, vectors use contiguous storage locations for their elements, 
// which means that their elements can also be accessed using offsets on regular pointers 
// to its elements, and just as efficiently as in arrays. But unlike arrays, their size can 
// change dynamically, with their storage being handled automatically by the container.

// Internally, vectors use a dynamically allocated array to store their elements. 
// This array may need to be reallocated in order to grow in size when new elements 
// are inserted, which implies allocating a new array and moving all elements to it. 
// This is a relatively expensive task in terms of processing time, and thus, 
// vectors do not reallocate each time an element is added to the container.

// Instead, vector containers may allocate some extra storage to accommodate for possible growth, 
// and thus the container may have an actual capacity greater than the storage strictly needed 
// to contain its elements (i.e., its size). Libraries can implement different strategies 
// for growth to balance between memory usage and reallocations, but in any case, reallocations 
// should only happen at logarithmically growing intervals of size so that the insertion of 
// individual elements at the end of the vector can be provided with amortized constant time 
// complexity (see push_back).

// Therefore, compared to arrays, vectors consume more memory in exchange for the ability 
// to manage storage and grow dynamically in an efficient way.

// Compared to the other dynamic sequence containers (deques, lists and forward_lists), 
// vectors are very efficient accessing its elements (just like arrays) and relatively 
// efficient adding or removing elements from its end. For operations that involve inserting 
// or removing elements at positions other than the end, they perform worse than the others, 
// and have less consistent iterators and references than lists and forward_lists.

// Container properties

// Sequence        : Elements in sequence containers are ordered in a strict linear sequence. 
//                   Individual elements are accessed by their position in this sequence.
// Dynamic array   : Allows direct access to any element in the sequence, 
//                   even through pointer arithmetics, and provides relatively fast 
//                   addition/removal of elements at the end of the sequence.
// Allocator-aware : The container uses an allocator object to dynamically handle its storage needs. 

#include <iostream>
#include <vector>
#include <functional>

void print(auto const & v) {
    for (auto const & n: v) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
}

int main()
{
    std::cout << "Creating our vector" << std::endl;
    std::vector<int> v { 0, 1, 2, 3, 4, 5};
    print(v);
    std::cout << "Adding elements at the end using vector::push_back" << std::endl;
    v.push_back(11);
    v.push_back(12);
    v.push_back(13);
    print(v);
    std::cout << "Inserting element after the third position using vector::insert" << std::endl;
    std::vector<int>::iterator it = std::begin(v);
    std:advance(it, 3);
    it = v.insert(it, 8);
    print(v);
    std::cout << "Removing element at the 8th position using vector::erase" << std::endl;
    std::advance(it, 4);
    v.erase(it);
    print(v);
    std::cout << "Removing the last element using vector::pop_back" << std::endl;
    v.pop_back();
    print(v);

    return 0;
}