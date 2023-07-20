#include <iostream>
#include <string>
#include <utility>

// Rule of Five
// Because the presence of a user-defined (or = default or = delete declared) destructor,
// copy-constructor, or copy-assignment operator prevents implicit definition of the
// move-constructor and the move assignment operator, any class for which move semantics
// are desirable, has to declare all five special member functions

struct Data
{
    std::string id;
};

class RuleOfFive
{
private:
    Data *data;

public:
    RuleOfFive(std::string id) : data{new Data{id}} {}
    ~RuleOfFive() // I - Destructor
    {
        delete data;
        data = nullptr;
    }
    RuleOfFive(RuleOfFive const &other) : RuleOfFive{other.data->id} {} // II - Copy Constructor
    RuleOfFive &operator=(RuleOfFive const &other)                       // III - Copy Assignment
    {
        return *this = RuleOfFive(other);
    }
    RuleOfFive(RuleOfFive &&other) noexcept // IV - Move Constructor
    : data{std::exchange(other.data, nullptr)}
    {
        std::cout << "Move constructor" << std::endl;
    }
    RuleOfFive& operator=(RuleOfFive &&other) // V - Move Assignment
    {
        std::cout << "Move assignment" << std::endl;
        if (this != &other) {
            data = std::exchange(other.data, nullptr); // move data, while leaving nullptr in other.data
        }
        return *this;
    }
    void identify()
    {
        if (data)
            std::cout << "Rule Of Five : Data ID : " << data->id << std::endl;
        else
            std::cout << "I'm no longer the owner of ID" << std::endl;
    }
};

int main()
{
    RuleOfFive o1{"ID-01"};
    o1.identify();
    RuleOfFive o2{o1}; // I - Uses Copy Constructor
    o2.identify();
    RuleOfFive o3{"ID-03"};
    o3.identify();
    o3 = o2; // II - Uses Copy Assignment;
    o3.identify();
    RuleOfFive o4{"ID-04"};
    o4.identify();
    RuleOfFive o5 {std::move(o4)}; // IV - Uses Move Constructor
    o4.identify();
    o5.identify();
    o4 = std::move(o5); // V - Uses Move Assignment
    o4.identify();
    o5.identify();

    return 0;
} // III - All destructors are called here

// Unlike Rule of Three, failing to provide move constructor and move assignment is usually
// not an error, but a missed optimization opportunity.