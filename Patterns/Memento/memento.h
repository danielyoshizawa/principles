#pragma once

#include <string>

class Memento
{
private:
    std::string state;
public:
    virtual ~Memento() = default;
    Memento(const std::string & state);
    std::string State() const;
};
