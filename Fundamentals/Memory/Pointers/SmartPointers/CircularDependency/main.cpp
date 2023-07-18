// Here we are ilustrating the circular dependency problem
// that happens when an object reference the next, and the
// last one references the firts.
// The example used here came from learncpp.com
// https://www.learncpp.com/cpp-tutorial/circular-dependency-issues-with-stdshared_ptr-and-stdweak_ptr/
// And the solution to the problem will be shown on the Weak Ptr project

#include <iostream>
#include <memory> // for std::shared_ptr
#include <string>

class Person
{
    std::string m_name;
    std::shared_ptr<Person> m_partner; // initially created empty

public:
    Person(const std::string &name) : m_name(name)
    {
        std::cout << m_name << " created\n";
    }
    ~Person()
    {
        std::cout << m_name << " destroyed\n";
    }

    friend bool partnerUp(std::shared_ptr<Person> &p1, std::shared_ptr<Person> &p2)
    {
        if (!p1 || !p2)
            return false;

        // Creating the circular dependency
        p1->m_partner = p2;
        p2->m_partner = p1;

        std::cout << p1->m_name << " is now partnered with " << p2->m_name << '\n';

        return true;
    }
};

int main()
{
    std::shared_ptr<Person> lucy{std::make_shared<Person>("Lucy")};   // create a Person named "Lucy"
    std::shared_ptr<Person> ricky{std::make_shared<Person>("Ricky")}; // create a Person named "Ricky"

    partnerUp(lucy, ricky); // Make "Lucy" point to "Ricky" and vice-versa

    return 0;
}

// From Valgrind
// ==6589== HEAP SUMMARY:
// ==6589==     in use at exit: 128 bytes in 2 blocks
// ==6589==   total heap usage: 4 allocs, 2 frees, 73,856 bytes allocated
// ==6589== 
// ==6589== LEAK SUMMARY:
// ==6589==    definitely lost: 64 bytes in 1 blocks
// ==6589==    indirectly lost: 64 bytes in 1 blocks
// ==6589==      possibly lost: 0 bytes in 0 blocks
// ==6589==    still reachable: 0 bytes in 0 blocks
// ==6589==         suppressed: 0 bytes in 0 blocks
