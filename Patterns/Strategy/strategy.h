#pragma once

class Strategy
{
public:
    virtual ~Strategy() = default;
    virtual int AddTo(int value) = 0;
};
