#include <iostream>

// Rule of Zero
// Classes that have custom destructors, copy/move constructors or copy/move assignment operators
// should deal exclusively with ownership (which follows from the Single Responsibility Principle).
// Other classes should not have custom destructors, copy/move constructors or copy/move assignment
// operators.

class RuleOfZero
{
    std::string data;

public:
    RuleOfZero(const std::string &arg) : data{arg} {}
    void identify() {
        std::cout << "Data : " << data << std::endl;
    }
};

// When a base class is intended for polymorphic use, its destructor may have to be declared
// public or virtual. This blocks implicit moves (and deprecates implicit copies), and so the
// special member functions have to be declared as defaulted.

class BaseOfFiveDefaults
{
public:
    BaseOfFiveDefaults(BaseOfFiveDefaults const &) = default;
    BaseOfFiveDefaults(BaseOfFiveDefaults &&) = default;
    BaseOfFiveDefaults &operator=(BaseOfFiveDefaults const &) = default;
    BaseOfFiveDefaults &operator=(BaseOfFiveDefaults &&) = default;
    virtual ~BaseOfFiveDefaults() = default;
};

// However, this makes the class prone to slicing, which is why polymorphic classes often
// define copy as deleted,which leads to the following generic wording for the Rule of Five
// - If you define or =delete any default operation, define or =delete them all.

int main()
{
    RuleOfZero o1{"ID-01"};
    o1.identify();
    RuleOfZero o2{o1}; // I - Default Copy Constructor
    o2.identify();
    RuleOfZero o3{"ID-03"};
    o3.identify();
    o3 = o2; // II - Default Copy Assignment
    o3.identify();
    RuleOfZero o4{std::move(o3)}; // III - Default Move Constructor
    o4.identify();
    o3.identify();
    o3 = std::move(o4); // IV - Default Move Assignment
    o4.identify();
    o3.identify();

    return 0;
} // V - Default Destructor