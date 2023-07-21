// Maps are associative containers that store elements formed by a combination of a key value
// and a mapped value, following a specific order.
// In a map, the key values are generally used to sort and uniquely identify the elements,
// while the mapped values store the content associated to this key.
// The types of key and mapped value may differ, and are grouped together
// in member type value_type.
// Internally, the elements in a map are always sorted by its key following a
// specific strict weak ordering criterion indicated by its internal comparison object
// (of type Compare).
// map containers are generally slower than unordered_map containers to access individual
// elements by their key, but they allow the direct iteration on subsets based on their order.
// The mapped values in a map can be accessed directly by their corresponding key using the
// bracket operator ((operator[]).
// Maps are typically implemented as binary search trees.

// Container properties

// Associative     : Elements in associative containers are referenced by their key
//                   and not by their absolute position in the container.
// Ordered         : The elements in the container follow a strict order at all times.
//                   All inserted elements are given a position in this order.
// Map             : Each element associates a key to a mapped value: Keys are meant to identify
//                   the elements whose main content is the mapped value.
// Unique keys     : No two elements in the container can have equivalent keys.
// Allocator-aware : The container uses an allocator object to dynamically handle its storage needs.

#include <iostream>
#include <map>
#include <string>

void printElements(const auto &mp)
{
    for (const auto &n : mp)
    {
        std::cout << "["<< n.first << " => " << n.second << "]";
    }
    std::cout << std::endl;
}

int main()
{
    std::cout << "Creating our map" << std::endl;
    std::map<std::string, int> mp;
    std::cout << "Adding multiple key/value to our map map::insert" << std::endl;
    mp.insert(std::pair<std::string, int>{"a", 5});
    mp.insert(std::pair<std::string, int>{"b", 8});
    mp.insert(std::pair<std::string, int>{"c", 4});
    mp.insert(std::pair<std::string, int>{"d", 2});
    printElements(mp);
    std::cout << "Accessing the element with the key 'c' map::at" << std::endl;
    std::cout << "[c => " << mp.at("c") << "]" << std::endl;
    std::cout << "Changing the element value from 4 to 6 map::at" << std::endl;
    mp.at("c") = 6;
    std::cout << "[c => " << mp.at("c") << "]" << std::endl;
    printElements(mp);
    std::cout << "Finding the element b using map::find" << std::endl;
    std::map<std::string, int>::iterator it {mp.find("b")};
    std::cout << "[" << (*it).first << " => " << (*it).second << "]" << std::endl;
    std::cout << "Using the found element as a hint in map::emplace_hint" << std::endl;
    mp.emplace_hint(it, "bb", 10);
    printElements(mp);

    return 0;
}