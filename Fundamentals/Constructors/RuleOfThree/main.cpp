#include <iostream>
#include <string>

// Rule of Three
// If a class requires a user-defined destructor, a user-defined copy constructor,
// or a user-defined copy assignment operator, it almost certainly requires all three.

struct Data
{
    std::string id;
};

class RuleOfThree
{
private:
    Data *data;

public:
    RuleOfThree(std::string id) : data{new Data{id}} {}
    ~RuleOfThree()
    { // I - Destructor
        delete data;
        data = nullptr;
    }
    RuleOfThree(RuleOfThree const &other) : RuleOfThree{other.data->id} {} // II - Copy Constructor
    RuleOfThree &operator=(RuleOfThree const &other)                       // III - Copy Assignment
    {
        if (this == &other)
        {
            return *this;
        }
        delete data;
        data = new Data{other.data->id};

        return *this;
    }
    void identify()
    {
        std::cout << "Rule Of Three : Data ID : " << data->id << std::endl;
    }
};

int main()
{
    RuleOfThree o1{"ID-01"};
    o1.identify();
    RuleOfThree o2{o1}; // I - Uses Copy Constructor
    o2.identify();
    RuleOfThree o3{"ID-03"};
    o3.identify();
    o3 = o2; // II - Uses Copy Assignment;
    o3.identify();

    return 0;
} // III - All destructors are called here