#pragma once

class Strategy;
class Context
{
private:
    Strategy * strategy_;
public:
    virtual ~Context() = default;
    Context() = default;

    void SetStrategy(Strategy * strategy);
    void UseStrategy();
};
