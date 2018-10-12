#pragma once

#include <string>

class Colleague
{
private:
    std::string name;
    bool status;
public:
    virtual ~Colleague() = default;
    Colleague(const std::string & name);

    std::string Name() const;
    void isOn(bool is);
    bool isOn() const;
};
