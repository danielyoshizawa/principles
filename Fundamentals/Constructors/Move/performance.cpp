// On this example, we will do a simple
// performance mesure, the time that each
// version takes to allocate 1000 objects
// of a costly data.
#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <thread>
#include <StopWatch.h>

class Data
{
public:
    Data()
    {
        // To slow down the data creation process
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
};

class Copyable
{
private:
    Data *data;

public:
    Copyable() : data{new Data} {}
    Copyable(const Copyable &copyable)
    {
        data = new Data{};
    }
    Copyable &operator=(const Copyable &copyable)
    {
        data = new Data{};
        return *this;
    }
};

class Movable
{
private:
    Data *data;

public:
    Movable() : data{new Data{}} {}
    Movable(Movable &&movable)
    {
        data = movable.data;
        movable.data = nullptr;
    }
    Movable &operator=(Movable &&movable)
    {
        if (&movable == this)
        {
            return *this;
        }
        delete data;
        data = movable.data;
        movable.data = nullptr;

        return *this;
    }
};

int main()
{
    std::vector<Copyable> copyVector;

    {
        StopWatch sw{"Copyable timer"};
        for (int i{0}; i < 1000; ++i)
        {
            copyVector.push_back(Copyable{});
        }
    }

    std::vector<Movable> moveVector;

    {
        StopWatch sw{"Movable timer"};
        for (int i{0}; i < 1000; ++i)
        {
            moveVector.push_back(Movable{});
        }
    }
    return 0;
}

// Output on my machine
// Copyable timer : 3302.67 ms
// Movable timer : 1091.02 ms