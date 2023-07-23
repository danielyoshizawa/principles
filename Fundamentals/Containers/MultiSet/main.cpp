// Multiple-Key Set (Multiset)
// Multisets are containers that store elements following a specific order,
// and where multiple elements can have equivalent values.

// In a multiset, the value of an element also identifies it (the value is itself the key, of type T).
// The value of the elements in a multiset cannot be modified once in the container
// (the elements are always const), but they can be inserted or removed from the container.

// Internally, the elements in a multiset are always sorted following a specific
// strict weak ordering criterion indicated by its internal comparison object (of type Compare).

// multiset containers are generally slower than unordered_multiset containers to
// access individual elements by their key, but they allow the direct iteration on
// subsets based on their order.

// Multisets are typically implemented as binary search trees.

// Container properties

// Associative              : Elements in associative containers are referenced by their key
//                            and not by their absolute position in the container.
// Ordered                  : The elements in the container follow a strict order at all times.
//                            All inserted elements are given a position in this order.
// Set                      : The value of an element is also the key used to identify it.
// Multiple equivalent keys : Multiple elements in the container can have equivalent keys.
// Allocator-aware          : The container uses an allocator object to dynamically handle
//                            its storage needs.

#include <iostream>
#include <set> // multiset

void print(auto const &m)
{
    for (auto &n : m)
    {
        std::cout << n << " ";
    }
    std::cout << std::endl;
}

int main()
{
    std::cout << "Creating our multiset" << std::endl;
    std::multiset<int> ms;
    std::cout << "Inserting elements using multiset::insert" << std::endl;
    ms.insert(12);
    ms.insert(5);
    ms.insert(8);
    ms.insert(12);
    ms.insert(9);
    ms.insert(5);
    ms.insert(6);
    ms.insert(9);
    ms.insert(9);
    print(ms);
    std::cout << "Removing eletment 12 (repeated) multiset::erase" << std::endl;
    ms.erase(12);
    print(ms);
    std::cout << "Removing fourth element by its position multiset::erase" << std::endl;
    std::multiset<int>::const_iterator it = std::begin(ms);
    std::advance(it, 3);
    ms.erase(it);
    print(ms);
    std::cout << "Getting all elements 9 multiset::equal_range" << std::endl;
    std::pair<std::multiset<int>::iterator,std::multiset<int>::iterator> ret = ms.equal_range(9);

    for (auto it1 {ret.first}; it1 != ret.second; ++it1) {
        std::cout << *it1 << " ";
    }

    std::cout << std::endl;

    return 0;
}