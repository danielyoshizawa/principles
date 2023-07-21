// Set
// Sets are containers that store unique elements following a specific order.

// In a set, the value of an element also identifies it (the value is itself the key, of type T),
// and each value must be unique. The value of the elements in a set cannot be modified once in
// the container (the elements are always const), but they can be inserted or removed from the
// container.

// Internally, the elements in a set are always sorted following a specific strict weak ordering
// criterion indicated by its internal comparison object (of type Compare).

// set containers are generally slower than unordered_set containers to access individual elements
// by their key, but they allow the direct iteration on subsets based on their order.

// Sets are typically implemented as binary search trees.

// Container properties
// Associative     : Elements in associative containers are referenced by their key and
//                   not by their absolute position in the container.
// Ordered         : The elements in the container follow a strict order at all times.
//                   All inserted elements are given a position in this order.
// Set             : The value of an element is also the key used to identify it.
// Unique keys     : No two elements in the container can have equivalent keys.
// Allocator-aware : The container uses an allocator object to dynamically handle its storage needs.

#include <iostream>
#include <set>

void print(const auto & s)
{
    for (auto & n : s) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
}

int main()
{
    std::cout << "Creating our set" << std::endl;
    std::set<int> st;
    std::cout << "Adding elements using set::insert" << std::endl;
    st.insert(0);
    st.insert(1);
    st.insert(2);
    st.insert(3);
    print(st);
    std::cout << "Removing elements using set::erase" << std::endl;
    st.erase(2);
    print(st);
    std::cout << "Trying to add an existing element set::insert" << std::endl;
    st.insert(1);
    print(st);

    return 0;
}