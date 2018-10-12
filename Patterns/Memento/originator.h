#pragma once

#include <string>

class Memento;
class Originator
{
private:
    std::string state_;
public:
    virtual ~Originator() = default;
    Originator() = default;
    void State(const std::string & state);
    Memento * Create();
    void Restore(const Memento & memento);
};
