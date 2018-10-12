#pragma once

#include <vector>

class Colleague;
class Mediator
{
private:
    std::vector<Colleague *> colleagueVector;
public:
    virtual ~Mediator() = default;
    Mediator() = default;
    void AddColleague(Colleague * colleague);
    void CallColleague(Colleague * colleague);
};
