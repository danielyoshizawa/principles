// Multimaps are associative containers that store elements formed by a
// combination of a key value and a mapped value, following a specific order,
// and where multiple elements can have equivalent keys.
// Multimaps are typically implemented as binary search trees.

// Container properties

// Associative              : Elements in associative containers are referenced by their key
//                            and not by their absolute position in the container.
// Ordered                  : The elements in the container follow a strict order at all times.
//                            All inserted elements are given a position in this order.
// Map                      : Each element associates a key to a mapped value:
//                            Keys are meant to identify the elements whose main content is
//                            the mapped value.
// Multiple equivalent keys : Multiple elements in the container can have equivalent keys.
// Allocator-aware          : The container uses an allocator object to dynamically handle
//                            its storage needs.

#include <iostream>
#include <map> // multimap

void print(const auto &n, bool eol = false)
{
    std::cout << "[" << n.first << " => " << n.second << "]";
    if (eol) std::cout << std::endl;
}

void printElements(const auto &mp)
{
    for (const auto &n : mp)
    {
        print(n);
    }
    std::cout << std::endl;
}

typedef std::multimap<char,int>::iterator mmIterator;

int main()
{
    std::cout << "Creating our multimap" << std::endl;
    std::multimap<char, int> mm;
    std::cout << "Adding multiple key/value to our multimap multimap::insert" << std::endl;
    mm.insert(std::pair<char, int>{'a', 5});
    mm.insert(std::pair<char, int>{'b', 8});
    mm.insert(std::pair<char, int>{'c', 4});
    mm.insert(std::pair<char, int>{'d', 2});
    mm.insert(std::pair<char, int>{'c', 7});
    mm.insert(std::pair<char, int>{'b', 1});
    printElements(mm);
    std::cout << "Using find to get the b key multimap::find" << std::endl;
    std::multimap<char, int>::iterator it{mm.find('b')};
    print(*it, true);
    std::cout << "Using equal range to get all b keys multimap::equal_range" << std::endl;
    std::pair<mmIterator, mmIterator> ret {mm.equal_range('b')};

    for (mmIterator it = ret.first; it != ret.second; ++it) {
        print((*it), true);
    }

    return 0;
};